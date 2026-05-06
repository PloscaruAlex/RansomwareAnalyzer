#include "processes_threads.h"

std::string JoinArgv(INT argc, const CHAR* const* argv) {
    std::ostringstream oss;
    for (int i = 0; i < argc; ++i) {
        if (i) oss << ' ';
        oss << argv[i];
    }
    return oss.str();
}

BOOL OnFollowChild(CHILD_PROCESS childProcess, VOID* v) {
    int argc = 0;
    const char* const* argv = 0;
    CHILD_PROCESS_GetCommandLine(childProcess, &argc, &argv);

    std::string cmd = JoinArgv(argc, argv);

    std::ostringstream oss;
    oss << "{"
        << "\"timestamp\":\"" << Logger::JsonEscape(Logger::MakeTimestamp()) << "\","
        << "\"timestamp_ms\":" << Logger::MakeTimestampMs() << ","
        << "\"event\":\"child_process\","
        << "\"parent_pid\":" << PIN_GetPid() << ","
        << "\"child_pid\":" << CHILD_PROCESS_GetId(childProcess) << ","
        << "\"argc\":" << argc << ","
        << "\"command_line\":\"" << Logger::JsonEscape(cmd) << "\""
        << "}";

    Logger::Instance().LogProcess(oss.str(), PIN_ThreadId());

    return true;
}

VOID OnThreadStart(THREADID tid, CONTEXT* ctxt, INT32 flags, VOID* v) {
    std::ostringstream oss;
    oss << "{"
        << "\"timestamp\":\"" << Logger::JsonEscape(Logger::MakeTimestamp()) << "\","
        << "\"timestamp_ms\":" << Logger::MakeTimestampMs() << ","
        << "\"event\":\"thread_start\","
        << "\"pid\":" << PIN_GetPid() << ","
        << "\"thread_id\":" << tid << ","
        << "\"flags\":" << flags
        << "}";

    Logger::Instance().LogProcess(oss.str(), tid);
}

void StartProcessesThreadsModule() {
    PIN_AddFollowChildProcessFunction(OnFollowChild, 0);
    PIN_AddThreadStartFunction(OnThreadStart, 0);
}

void FinishProcessesThreadsModule() {
    Logger::Instance().LogMain("Processes and threads events module stopping -> Check ProcessThread.jsonl for child processes and thread starts events.");
}
