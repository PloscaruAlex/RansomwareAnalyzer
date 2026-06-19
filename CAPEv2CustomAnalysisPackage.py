import os
import time
import ctypes
import ctypes.wintypes
import pefile
import glob
import shutil
import subprocess

from lib.common.abstracts import Package
from lib.common.exceptions import CuckooPackageError
from lib.common.common import check_file_extension
from lib.api.process import Process
from lib.common.results import upload_to_host
from lib.common.constants import OPT_EXECUTIONDIR

import logging
log = logging.getLogger(__name__)


PIN_PATH = "C:\\pin\\pin\\pin.exe"
DLL_32   = "C:\\pin\\pin\\source\\tools\\RansomwareAnalyzer\\obj-ia32\\RansomwareAnalyzer.dll"
DLL_64   = "C:\\pin\\pin\\source\\tools\\RansomwareAnalyzer\\obj-intel64\\RansomwareAnalyzer.dll"
LOG_DIR  = "C:\\pin\\logs"
LOG_GLOBS = ["*.jsonl", "RansomwareAnalyzer*.log", "pintool.log", "pin.log"]

PINTOOL_OUTPUT_KNOB = None

PIN_CHILD_INITIAL_WAIT = 5 
PIN_CHILD_MAX_POLLS    = 10

MALWARE_EXIT_TIMEOUT = 30


def _snapshot_all_processes():
    TH32CS_SNAPPROCESS = 0x00000002

    class PROCESSENTRY32(ctypes.Structure):
        _fields_ = [
            ("dwSize",               ctypes.wintypes.DWORD),
            ("cntUsage",             ctypes.wintypes.DWORD),
            ("th32ProcessID",        ctypes.wintypes.DWORD),
            ("th32DefaultHeapID",    ctypes.POINTER(ctypes.c_ulong)),
            ("th32ModuleID",         ctypes.wintypes.DWORD),
            ("cntThreads",           ctypes.wintypes.DWORD),
            ("th32ParentProcessID",  ctypes.wintypes.DWORD),
            ("pcPriClassBase",       ctypes.c_long),
            ("dwFlags",              ctypes.wintypes.DWORD),
            ("szExeFile",            ctypes.c_char * 260),
        ]

    k32  = ctypes.windll.kernel32
    snap = k32.CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0)
    if snap == ctypes.wintypes.HANDLE(-1).value:
        log.error("CreateToolhelp32Snapshot failed (GLE=0x%X)", k32.GetLastError())
        return {}

    procs = {}
    entry = PROCESSENTRY32()
    entry.dwSize = ctypes.sizeof(PROCESSENTRY32)
    try:
        if k32.Process32First(snap, ctypes.byref(entry)):
            while True:
                pid    = entry.th32ProcessID
                parent = entry.th32ParentProcessID
                name   = entry.szExeFile.decode("utf-8", errors="replace").lower()
                procs[pid] = (parent, name)
                if not k32.Process32Next(snap, ctypes.byref(entry)):
                    break
    finally:
        k32.CloseHandle(snap)
    return procs


def _snapshot_children(parent_pid):
    procs = _snapshot_all_processes()
    return [pid for pid, (ppid, _) in procs.items() if ppid == parent_pid]


def _find_non_pin_in_subtree(snapshot, root_pid, pin_exe_name="pin.exe"):
    visited = set()
    queue   = [root_pid]
    while queue:
        pid = queue.pop(0)
        if pid in visited:
            continue
        visited.add(pid)
        if pid != root_pid and pin_exe_name not in snapshot.get(pid, (0, ""))[1]:
            return pid
        for child_pid, (ppid, _) in snapshot.items():
            if ppid == pid and child_pid not in visited:
                queue.append(child_pid)
    return None



class RansomwareAnalyzer(Package):
    summary = "Runs the sample under RansomwareAnalyzer pintool (32 or 64-bit)."

    _pin_pid:      int = 0   
    _malware_pid:  int = 0 
    _malware_path: str = ""


    def start(self, path):
        path = check_file_extension(path, ".exe")
        self._malware_path = path

        if not os.path.exists(PIN_PATH):
            raise CuckooPackageError(f"pin.exe not found: {PIN_PATH}")

        os.makedirs(LOG_DIR, exist_ok=True)
        self.options[OPT_EXECUTIONDIR] = LOG_DIR

        try:
            pe      = pefile.PE(path)
            machine = pe.FILE_HEADER.Machine
        except Exception as exc:
            raise CuckooPackageError(f"Cannot parse PE headers for '{path}': {exc}")

        if machine == 0x14C: 
            architecture = 32
            if not os.path.exists(DLL_32):
                raise CuckooPackageError(f"32-bit DLL not found: {DLL_32}")
        else:
            architecture = 64
            if not os.path.exists(DLL_64):
                raise CuckooPackageError(f"64-bit DLL not found: {DLL_64}")
            if machine != 0x8664:
                log.warning("Unknown machine type 0x%X - defaulting to 64-bit.", machine)

        pin_log   = os.path.join(LOG_DIR, "pin.log")
        knob_args = f'{PINTOOL_OUTPUT_KNOB} "{LOG_DIR}"' if PINTOOL_OUTPUT_KNOB else ""

        if architecture == 32:
            args = (
                f'-follow_execv '
                f'-logfile "{pin_log}" '
                f'-t "{DLL_32}" {knob_args} '
                f'-- "{path}"'
            )
        else:
            args = (
                f'-follow_execv '
                f'-logfile "{pin_log}" '
                f'-t64 "{DLL_64}" {knob_args} '
                f'-t  "{DLL_32}" {knob_args} '
                f'-- "{path}"'
            )

        log.info("Launching pin.exe (%d-bit): %s", architecture, args)

        pre_launch_pids = set(_snapshot_all_processes().keys())

        p = Process()
        if not p.execute(path=PIN_PATH, args=args, suspended=False):
            raise CuckooPackageError("Failed to launch Intel Pin. Analysis aborted.")
        
        BELOW_NORMAL_PRIORITY_CLASS = 0x00004000
        k32 = ctypes.windll.kernel32
        handle = k32.OpenProcess(0x0200, False, p.pid)
        if handle:
            k32.SetPriorityClass(handle, BELOW_NORMAL_PRIORITY_CLASS)
            k32.CloseHandle(handle)

        self._pin_pid = p.pid
        log.info("pin.exe started with PID %d", self._pin_pid)

        malware_pid = self._wait_for_child(self._pin_pid, pre_launch_pids)

        if malware_pid is None:
            log.warning(
                "No child process found under pin.exe PID %d after %d polls. "
                "Falling back to tracking pin.exe - analysis may terminate early.",
                self._pin_pid, PIN_CHILD_MAX_POLLS,
            )
            return self._pin_pid

        self._malware_pid = malware_pid
        self._inject_cape(malware_pid, path)
        return malware_pid


    def _wait_for_child(self, pin_pid, pre_launch_pids=None):
        pin_exe_name = os.path.basename(PIN_PATH).lower()

        log.info("Waiting %ds for PIN to spawn its child process...", PIN_CHILD_INITIAL_WAIT)
        time.sleep(PIN_CHILD_INITIAL_WAIT)

        for attempt in range(PIN_CHILD_MAX_POLLS):
            snapshot = _snapshot_all_processes()

            pid = _find_non_pin_in_subtree(snapshot, pin_pid, pin_exe_name)
            if pid:
                log.info(
                    "Found malware PID %d (%s) via subtree walk (poll %d/%d).",
                    pid, snapshot.get(pid, (0, "?"))[1], attempt + 1, PIN_CHILD_MAX_POLLS,
                )
                return pid

            if pre_launch_pids is not None:
                for new_pid, (_, exe_name) in snapshot.items():
                    if new_pid not in pre_launch_pids and pin_exe_name not in exe_name:
                        log.info(
                            "Found malware PID %d (%s) via new-process diff (poll %d/%d).",
                            new_pid, exe_name, attempt + 1, PIN_CHILD_MAX_POLLS,
                        )
                        return new_pid

            log.debug("Child not yet visible (poll %d/%d).", attempt + 1, PIN_CHILD_MAX_POLLS)
            time.sleep(1)

        return None

    def _inject_cape(self, pid, interest_path):
        try:
            proc = Process(config=self.config, pid=pid)
            proc.inject(interest=interest_path)
            if pid not in self.pids:
                self.pids.append(pid)
            log.info("CAPE monitor injected into malware PID %d.", pid)
        except Exception as exc:
            log.warning(
                "Could not inject CAPE monitor into PID %d: %s. "
                "Pintool logs will still be gathered; CAPE API data will be absent.",
                pid, exc,
            )

    def _all_malware_pids(self):
        root = self._malware_pid or self._pin_pid
        if not root:
            return []

        visited = set()
        ordered = []
        queue   = [root]

        while queue:
            pid = queue.pop(0)
            if pid in visited:
                continue
            visited.add(pid)
            ordered.append(pid)
            queue.extend(_snapshot_children(pid))

        return ordered

    def _wait_for_malware_exit(self):
        pids = self._all_malware_pids()
        if not pids:
            log.warning("_wait_for_malware_exit: no malware PIDs found - skipping wait.")
            return

        log.info(
            "Waiting up to %ds for malware process tree to exit (PIDs: %s)...",
            MALWARE_EXIT_TIMEOUT, pids,
        )

        SYNCHRONIZE       = 0x00100000
        PROCESS_TERMINATE = 0x0001
        WAIT_OBJECT_0     = 0x00000000

        k32      = ctypes.windll.kernel32
        deadline = time.time() + MALWARE_EXIT_TIMEOUT

        for pid in pids:
            remaining_ms = max(0, int((deadline - time.time()) * 1000))

            handle = k32.OpenProcess(SYNCHRONIZE | PROCESS_TERMINATE, False, pid)
            if not handle:
                log.info("PID %d: already exited.", pid)
                continue

            try:
                result = k32.WaitForSingleObject(handle, remaining_ms)
                if result == WAIT_OBJECT_0:
                    log.info("PID %d: exited cleanly - logs flushed.", pid)
                else:
                    log.warning(
                        "PID %d: did not exit within budget - force-killing "
                        "(logs for this process may be incomplete).", pid,
                    )
                    k32.TerminateProcess(handle, 1)
            finally:
                k32.CloseHandle(handle)

    def _log_search_dirs(self):
        candidates = [
            self.options.get(OPT_EXECUTIONDIR, LOG_DIR),
            os.path.dirname(PIN_PATH),
            os.path.dirname(self._malware_path),
            os.environ.get("TEMP", ""),
            os.environ.get("TMP", ""),
            os.getcwd(),
        ]
        seen = set()
        dirs = []
        for d in candidates:
            nd = os.path.normcase(os.path.abspath(d)) if d else ""
            if nd and nd not in seen and os.path.isdir(d):
                seen.add(nd)
                dirs.append(d)
        return dirs

    def _collect_logs(self):
        search_dirs = self._log_search_dirs()
        log.info("Searching for pintool logs in: %s", search_dirs)

        found = []
        seen  = set()
        for search_dir in search_dirs:
            for pattern in LOG_GLOBS:
                for fp in glob.glob(os.path.join(search_dir, pattern)):
                    norm = os.path.normcase(os.path.abspath(fp))
                    if os.path.isfile(fp) and norm not in seen:
                        seen.add(norm)
                        found.append((fp, os.path.basename(fp)))
                        log.info("Found pintool log: %s", fp)

        if not found:
            log.warning("No pintool logs matched %s in: %s", LOG_GLOBS, search_dirs)
        return found


    def check(self):
        return True

    def package_files(self):
        return []

    def finish(self):
        if self.options.get("procmemdump", False):
            for pid in self.pids:
                Process(pid=pid).dump_memory()

        self._wait_for_malware_exit()

        collected = self._collect_logs()
        if not collected:
            log.warning("finish(): no pintool logs found - nothing to upload.")
            return True

        os.makedirs(LOG_DIR, exist_ok=True)

        for src_path, name in collected:
            try:
                src_size = os.path.getsize(src_path)
            except OSError as exc:
                log.warning("Cannot stat '%s': %s - skipping.", src_path, exc)
                continue

            if src_size == 0:
                log.info("Skipping empty file: %s", src_path)
                continue

            dest_path = os.path.join(LOG_DIR, name)
            src_norm  = os.path.normcase(os.path.abspath(src_path))
            dest_norm = os.path.normcase(os.path.abspath(dest_path))

            upload_path = src_path
            if src_norm != dest_norm:
                try:
                    shutil.copy2(src_path, dest_path)
                    log.info("Copied: %s -> %s", src_path, dest_path)
                    upload_path = dest_path
                except Exception as exc:
                    log.warning(
                        "Could not copy '%s' to '%s': %s - uploading from source.",
                        src_path, dest_path, exc,
                    )

            cape_dest = os.path.join("CAPE", name)
            log.info("Uploading: %s -> %s  (%d bytes)", name, cape_dest, src_size)
            upload_to_host(upload_path, cape_dest)

        return True