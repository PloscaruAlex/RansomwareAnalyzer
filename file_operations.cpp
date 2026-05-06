#include "file_operations.h"

void LogHandleResult(const std::string& api, ADDRINT retValue, THREADID tid, const char* fieldName) {
    std::ostringstream body;
    body << "\"result\":{"
         << "\"" << fieldName << "\":\"0x" << std::hex << retValue << "\","
         << "\"success\":" << ((retValue != 0 && retValue != static_cast<ADDRINT>(-1)) ? "true" : "false")
         << "}";
    Logger::Instance().LogFileEvent(api, "after", body.str(), tid);
}

/*
    Microsoft Documentation: 
    https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilew
*/
VOID BeforeCreateFileW(
    THREADID tid,
    ADDRINT lpFileName,
    ADDRINT dwDesiredAccess,
    ADDRINT dwShareMode,
    ADDRINT lpSecurityAttributes,
    ADDRINT dwCreationDisposition,
    ADDRINT dwFlagsAndAttributes,
    ADDRINT hTemplateFile) {
    std::wstring fileName = ReadWideString(reinterpret_cast<const wchar_t*>(lpFileName));

    std::ostringstream body;
    body << "\"args\":{"
         << "\"lpFileName\":\"" << Logger::JsonEscape(convertWideToStr(fileName)) << "\","
         << "\"dwDesiredAccess\":\"0x" << std::hex << dwDesiredAccess << "\","
         << "\"dwShareMode\":\"0x" << std::hex << dwShareMode << "\","
         << "\"lpSecurityAttributes\":\"0x" << std::hex << lpSecurityAttributes << "\","
         << "\"dwCreationDisposition\":\"0x" << std::hex << dwCreationDisposition << "\","
         << "\"dwFlagsAndAttributes\":\"0x" << std::hex << dwFlagsAndAttributes << "\","
         << "\"hTemplateFile\":\"0x" << std::hex << hTemplateFile << "\""
         << "}";

    Logger::Instance().LogFileEvent("CreateFileW", "before", body.str(), tid);
}

VOID AfterCreateFileW(THREADID tid, ADDRINT retHandle) { LogHandleResult("CreateFileW", retHandle, tid); }

/*
    Microsoft Documentation: 
    https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-createfilea
*/
VOID BeforeCreateFileA(
    THREADID tid,
    ADDRINT lpFileName,
    ADDRINT dwDesiredAccess,
    ADDRINT dwShareMode,
    ADDRINT lpSecurityAttributes,
    ADDRINT dwCreationDisposition,
    ADDRINT dwFlagsAndAttributes,
    ADDRINT hTemplateFile) {
    std::string fileName = ReadAnsiString(reinterpret_cast<const char*>(lpFileName));

    std::ostringstream body;
    body << "\"args\":{"
         << "\"lpFileName\":\"" << Logger::JsonEscape(fileName) << "\","
         << "\"dwDesiredAccess\":\"0x" << std::hex << dwDesiredAccess << "\","
         << "\"dwShareMode\":\"0x" << std::hex << dwShareMode << "\","
         << "\"lpSecurityAttributes\":\"0x" << std::hex << lpSecurityAttributes << "\","
         << "\"dwCreationDisposition\":\"0x" << std::hex << dwCreationDisposition << "\","
         << "\"dwFlagsAndAttributes\":\"0x" << std::hex << dwFlagsAndAttributes << "\","
         << "\"hTemplateFile\":\"0x" << std::hex << hTemplateFile << "\""
         << "}";

    Logger::Instance().LogFileEvent("CreateFileA", "before", body.str(), tid);
}

VOID AfterCreateFileA(THREADID tid, ADDRINT retHandle) { LogHandleResult("CreateFileA", retHandle, tid); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-findfirstfilew
*/
VOID BeforeFindFirstFileW(THREADID tid, ADDRINT lpFileName, ADDRINT lpFindFileData) {
    std::wstring fileName = ReadWideString(reinterpret_cast<const wchar_t*>(lpFileName));

    std::ostringstream body;
    body << "\"args\":{"
         << "\"lpFileName\":\"" << Logger::JsonEscape(convertWideToStr(fileName)) << "\","
         << "\"lpFindFileData\":\"0x" << std::hex << lpFindFileData << "\""
         << "}";

    Logger::Instance().LogFileEvent("FindFirstFileW", "before", body.str(), tid);
}

VOID AfterFindFirstFileW(THREADID tid, ADDRINT retHandle) { LogHandleResult("FindFirstFileW", retHandle, tid); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-findfirstfilea
*/
VOID BeforeFindFirstFileA(THREADID tid, ADDRINT lpFileName, ADDRINT lpFindFileData) {
    std::string fileName = ReadAnsiString(reinterpret_cast<const char*>(lpFileName));

    std::ostringstream body;
    body << "\"args\":{"
         << "\"lpFileName\":\"" << Logger::JsonEscape(fileName) << "\","
         << "\"lpFindFileData\":\"0x" << std::hex << lpFindFileData << "\""
         << "}";

    Logger::Instance().LogFileEvent("FindFirstFileA", "before", body.str(), tid);
}

VOID AfterFindFirstFileA(THREADID tid, ADDRINT retHandle) { LogHandleResult("FindFirstFileA", retHandle, tid); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-findfirstfileexw
*/
VOID BeforeFindFirstFileExW(
    THREADID tid,
    ADDRINT lpFileName,
    ADDRINT fInfoLevelId,
    ADDRINT lpFindFileData,
    ADDRINT fSearchOp,
    ADDRINT lpSearchFilter,
    ADDRINT dwAdditionalFlags) {
    std::wstring fileName = ReadWideString(reinterpret_cast<const wchar_t*>(lpFileName));

    std::ostringstream body;
    body << "\"args\":{"
         << "\"lpFileName\":\"" << Logger::JsonEscape(convertWideToStr(fileName)) << "\","
         << "\"fInfoLevelId\":\"0x" << std::hex << fInfoLevelId << "\","
         << "\"lpFindFileData\":\"0x" << std::hex << lpFindFileData << "\","
         << "\"fSearchOp\":\"0x" << std::hex << fSearchOp << "\","
         << "\"lpSearchFilter\":\"0x" << std::hex << lpSearchFilter << "\","
         << "\"dwAdditionalFlags\":\"0x" << std::hex << dwAdditionalFlags << "\""
         << "}";

    Logger::Instance().LogFileEvent("FindFirstFileExW", "before", body.str(), tid);
}

VOID AfterFindFirstFileExW(THREADID tid, ADDRINT retHandle) { LogHandleResult("FindFirstFileExW", retHandle, tid); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-findfirstfileexa
*/
VOID BeforeFindFirstFileExA(
    THREADID tid,
    ADDRINT lpFileName,
    ADDRINT fInfoLevelId,
    ADDRINT lpFindFileData,
    ADDRINT fSearchOp,
    ADDRINT lpSearchFilter,
    ADDRINT dwAdditionalFlags) {
    std::string fileName = ReadAnsiString(reinterpret_cast<const char*>(lpFileName));

    std::ostringstream body;
    body << "\"args\":{"
         << "\"lpFileName\":\"" << Logger::JsonEscape(fileName) << "\","
         << "\"fInfoLevelId\":\"0x" << std::hex << fInfoLevelId << "\","
         << "\"lpFindFileData\":\"0x" << std::hex << lpFindFileData << "\","
         << "\"fSearchOp\":\"0x" << std::hex << fSearchOp << "\","
         << "\"lpSearchFilter\":\"0x" << std::hex << lpSearchFilter << "\","
         << "\"dwAdditionalFlags\":\"0x" << std::hex << dwAdditionalFlags << "\""
         << "}";

    Logger::Instance().LogFileEvent("FindFirstFileExA", "before", body.str(), tid);
}

VOID AfterFindFirstFileExA(THREADID tid, ADDRINT retHandle) { LogHandleResult("FindFirstFileExA", retHandle, tid); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-findnextfilew
*/
VOID BeforeFindNextFileW(THREADID tid, ADDRINT hFindFile, ADDRINT lpFindFileData) {
    std::ostringstream body;
    body << "\"args\":{"
         << "\"hFindFile\":\"0x" << std::hex << hFindFile << "\","
         << "\"lpFindFileData\":\"0x" << std::hex << lpFindFileData << "\""
         << "}";

    Logger::Instance().LogFileEvent("FindNextFileW", "before", body.str(), tid);
}

VOID AfterFindNextFileW(THREADID tid, ADDRINT retValue) { LogHandleResult("FindNextFileW", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-findnextfilea
*/
VOID BeforeFindNextFileA(THREADID tid, ADDRINT hFindFile, ADDRINT lpFindFileData) {
    std::ostringstream body;
    body << "\"args\":{"
         << "\"hFindFile\":\"0x" << std::hex << hFindFile << "\","
         << "\"lpFindFileData\":\"0x" << std::hex << lpFindFileData << "\""
         << "}";

    Logger::Instance().LogFileEvent("FindNextFileA", "before", body.str(), tid);
}

VOID AfterFindNextFileA(THREADID tid, ADDRINT retValue) { LogHandleResult("FindNextFileA", retValue, tid, "return"); }


/*
    Microsoft Documentation: 
    https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-readfile
*/
VOID BeforeReadFile(THREADID tid, ADDRINT hFile, ADDRINT lpBuffer, ADDRINT nNumberOfBytesToRead, ADDRINT lpNumberOfBytesRead, ADDRINT lpOverlapped) {
    std::ostringstream body;
    body << "\"args\":{"
         << "\"hFile\":\"0x" << std::hex << hFile << "\","
         << "\"lpBuffer\":\"0x" << std::hex << lpBuffer << "\","
         << "\"nNumberOfBytesToRead\":\"0x" << std::hex << nNumberOfBytesToRead << "\","
         << "\"lpNumberOfBytesRead\":\"0x" << std::hex << lpNumberOfBytesRead << "\","
         << "\"lpOverlapped\":\"0x" << std::hex << lpOverlapped << "\""
         << "}";
    Logger::Instance().LogFileEvent("ReadFile", "before", body.str(), tid);
}

VOID AfterReadFile(THREADID tid, ADDRINT retValue) { LogHandleResult("ReadFile", retValue, tid, "return"); }

/*
    Microsoft Documentation: 
    https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-writefile
*/
VOID BeforeWriteFile(THREADID tid, ADDRINT hFile, ADDRINT lpBuffer, ADDRINT nNumberOfBytesToWrite, ADDRINT lpNumberOfBytesWritten, ADDRINT lpOverlapped) {
    std::ostringstream body;
    body << "\"args\":{"
         << "\"hFile\":\"0x" << std::hex << hFile << "\"," 
         << "\"lpBuffer\":\"0x" << std::hex << lpBuffer << "\"," 
         << "\"nNumberOfBytesToWrite\":\"0x" << std::hex << nNumberOfBytesToWrite << "\"," 
         << "\"lpNumberOfBytesWritten\":\"0x" << std::hex << lpNumberOfBytesWritten << "\"," 
         << "\"lpOverlapped\":\"0x" << std::hex << lpOverlapped << "\""
         << "}";
    Logger::Instance().LogFileEvent("WriteFile", "before", body.str(), tid);
}

VOID AfterWriteFile(THREADID tid, ADDRINT retValue) { LogHandleResult("WriteFile", retValue, tid, "return"); }

/*
    Microsoft Documentation: 
    https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-setfilepointer
*/
VOID BeforeSetFilePointer(THREADID tid, ADDRINT hFile, ADDRINT lDistanceToMove, ADDRINT lpDistanceToMoveHigh, ADDRINT dwMoveMethod) {
    std::ostringstream body;
    body << "\"args\":{"
         << "\"hFile\":\"0x" << std::hex << hFile << "\"," 
         << "\"lDistanceToMove\":\"0x" << std::hex << lDistanceToMove << "\"," 
         << "\"lpDistanceToMoveHigh\":\"0x" << std::hex << lpDistanceToMoveHigh << "\"," 
         << "\"dwMoveMethod\":\"0x" << std::hex << dwMoveMethod << "\""
         << "}";
    Logger::Instance().LogFileEvent("SetFilePointer", "before", body.str(), tid);
}

VOID AfterSetFilePointer(THREADID tid, ADDRINT retValue) { LogHandleResult("SetFilePointer", retValue, tid, "return"); }

/*
    Microsoft Documentation: 
    https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-setfilepointerex
*/
VOID BeforeSetFilePointerEx(THREADID tid, ADDRINT hFile, ADDRINT liDistanceToMove, ADDRINT lpNewFilePointer, ADDRINT dwMoveMethod) {
    std::ostringstream body;
    body << "\"args\":{"
         << "\"hFile\":\"0x" << std::hex << hFile << "\"," 
         << "\"liDistanceToMove\":\"0x" << std::hex << liDistanceToMove << "\"," 
         << "\"lpNewFilePointer\":\"0x" << std::hex << lpNewFilePointer << "\"," 
         << "\"dwMoveMethod\":\"0x" << std::hex << dwMoveMethod << "\""
         << "}";
    Logger::Instance().LogFileEvent("SetFilePointerEx", "before", body.str(), tid);
}

VOID AfterSetFilePointerEx(THREADID tid, ADDRINT retValue) { LogHandleResult("SetFilePointerEx", retValue, tid, "return"); }

/*
    Microsoft Documentation: 
    https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getfilesize
*/
VOID BeforeGetFileSize(THREADID tid, ADDRINT hFile, ADDRINT lpFileSizeHigh) {
    std::ostringstream body;
    body << "\"args\":{"
         << "\"hFile\":\"0x" << std::hex << hFile << "\","
         << "\"lpFileSizeHigh\":\"0x" << std::hex << lpFileSizeHigh << "\""
         << "}";
    Logger::Instance().LogFileEvent("GetFileSize", "before", body.str(), tid);
}

VOID AfterGetFileSize(THREADID tid, ADDRINT retValue) { LogHandleResult("GetFileSize", retValue, tid, "return"); }

/*
    Microsoft Documentation: 
    https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getfilesizeex
*/
VOID BeforeGetFileSizeEx(THREADID tid, ADDRINT hFile, ADDRINT lpFileSize) {
    std::ostringstream body;
    body << "\"args\":{"
         << "\"hFile\":\"0x" << std::hex << hFile << "\","
         << "\"lpFileSize\":\"0x" << std::hex << lpFileSize << "\""
         << "}";
    Logger::Instance().LogFileEvent("GetFileSizeEx", "before", body.str(), tid);
}

VOID AfterGetFileSizeEx(THREADID tid, ADDRINT retValue) { LogHandleResult("GetFileSizeEx", retValue, tid, "return"); }

/*
    Microsoft Documentation: 
    https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getfiletype
*/
VOID BeforeGetFileType(THREADID tid, ADDRINT hFile) {
    std::ostringstream body;
    body << "\"args\":{"
         << "\"hFile\":\"0x" << std::hex << hFile << "\""
         << "}";
    Logger::Instance().LogFileEvent("GetFileType", "before", body.str(), tid);
}

VOID AfterGetFileType(THREADID tid, ADDRINT retValue) { LogHandleResult("GetFileType", retValue, tid, "return"); }

/*
    Microsoft Documentation: 
    https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-setfileattributesw
*/
VOID BeforeSetFileAttributesW(THREADID tid, ADDRINT lpFileName, ADDRINT dwFileAttributes) {
    std::wstring fileName = ReadWideString(reinterpret_cast<const wchar_t*>(lpFileName));

    std::ostringstream body;
    body << "\"args\":{"
         << "\"lpFileName\":\"" << Logger::JsonEscape(convertWideToStr(fileName)) << "\","
         << "\"dwFileAttributes\":\"0x" << std::hex << dwFileAttributes << "\""
         << "}";

    Logger::Instance().LogFileEvent("SetFileAttributesW", "before", body.str(), tid);
}

VOID AfterSetFileAttributesW(THREADID tid, ADDRINT retValue) { LogHandleResult("SetFileAttributesW", retValue, tid, "return"); }

/*
    Microsoft Documentation: 
    https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-setfileattributesa
*/
VOID BeforeSetFileAttributesA(THREADID tid, ADDRINT lpFileName, ADDRINT dwFileAttributes) {
    std::string fileName = ReadAnsiString(reinterpret_cast<const char*>(lpFileName));

    std::ostringstream body;
    body << "\"args\":{"
         << "\"lpFileName\":\"" << Logger::JsonEscape(fileName) << "\","
         << "\"dwFileAttributes\":\"0x" << std::hex << dwFileAttributes << "\""
         << "}";

    Logger::Instance().LogFileEvent("SetFileAttributesA", "before", body.str(), tid);
}

VOID AfterSetFileAttributesA(THREADID tid, ADDRINT retValue) { LogHandleResult("SetFileAttributesA", retValue, tid, "return"); }

/*
    Microsoft Documentation: 
    https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-copyfilew
*/
VOID BeforeCopyFileW(THREADID tid, ADDRINT lpExistingFileName, ADDRINT lpNewFileName, ADDRINT bFailIfExists) {
    std::wstring existingFileName = ReadWideString(reinterpret_cast<const wchar_t*>(lpExistingFileName));
    std::wstring newFileName = ReadWideString(reinterpret_cast<const wchar_t*>(lpNewFileName));

    std::ostringstream body;
    body << "\"args\":{"
         << "\"lpExistingFileName\":\"" << Logger::JsonEscape(convertWideToStr(existingFileName)) << "\","
         << "\"lpNewFileName\":\"" << Logger::JsonEscape(convertWideToStr(newFileName)) << "\","
         << "\"bFailIfExists\":\"0x" << std::hex << bFailIfExists << "\""
         << "}";

    Logger::Instance().LogFileEvent("CopyFileW", "before", body.str(), tid);
}

VOID AfterCopyFileW(THREADID tid, ADDRINT retValue) { LogHandleResult("CopyFileW", retValue, tid, "return"); }

/*
    Microsoft Documentation: 
    https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-copyfilea
*/
VOID BeforeCopyFileA(THREADID tid, ADDRINT lpExistingFileName, ADDRINT lpNewFileName, ADDRINT bFailIfExists) {
    std::string existingFileName = ReadAnsiString(reinterpret_cast<const char*>(lpExistingFileName));
    std::string newFileName = ReadAnsiString(reinterpret_cast<const char*>(lpNewFileName));

    std::ostringstream body;
    body << "\"args\":{"
         << "\"lpExistingFileName\":\"" << Logger::JsonEscape(existingFileName) << "\","
         << "\"lpNewFileName\":\"" << Logger::JsonEscape(newFileName) << "\","
         << "\"bFailIfExists\":\"0x" << std::hex << bFailIfExists << "\""
         << "}";

    Logger::Instance().LogFileEvent("CopyFileA", "before", body.str(), tid);
}

VOID AfterCopyFileA(THREADID tid, ADDRINT retValue) { LogHandleResult("CopyFileA", retValue, tid, "return"); }

/*
    Microsoft Documentation: 
    https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-copyfileexw
*/
VOID BeforeCopyFileExW(
    THREADID tid,
    ADDRINT lpExistingFileName,
    ADDRINT lpNewFileName,
    ADDRINT lpProgressRoutine,
    ADDRINT lpData,
    ADDRINT pbCancel,
    ADDRINT dwCopyFlags) {
    std::wstring existingFileName = ReadWideString(reinterpret_cast<const wchar_t*>(lpExistingFileName));
    std::wstring newFileName = ReadWideString(reinterpret_cast<const wchar_t*>(lpNewFileName));

    std::ostringstream body;
    body << "\"args\":{"
         << "\"lpExistingFileName\":\"" << Logger::JsonEscape(convertWideToStr(existingFileName)) << "\","
         << "\"lpNewFileName\":\"" << Logger::JsonEscape(convertWideToStr(newFileName)) << "\","
         << "\"lpProgressRoutine\":\"0x" << std::hex << lpProgressRoutine << "\","
         << "\"lpData\":\"0x" << std::hex << lpData << "\","
         << "\"pbCancel\":\"0x" << std::hex << pbCancel << "\","
         << "\"dwCopyFlags\":\"0x" << std::hex << dwCopyFlags << "\""
         << "}";

    Logger::Instance().LogFileEvent("CopyFileExW", "before", body.str(), tid);
}

VOID AfterCopyFileExW(THREADID tid, ADDRINT retValue) { LogHandleResult("CopyFileExW", retValue, tid, "return"); }

/*
    Microsoft Documentation: 
    https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-copyfileexa
*/
VOID BeforeCopyFileExA(
    THREADID tid,
    ADDRINT lpExistingFileName,
    ADDRINT lpNewFileName,
    ADDRINT lpProgressRoutine,
    ADDRINT lpData,
    ADDRINT pbCancel,
    ADDRINT dwCopyFlags) {
    std::string existingFileName = ReadAnsiString(reinterpret_cast<const char*>(lpExistingFileName));
    std::string newFileName = ReadAnsiString(reinterpret_cast<const char*>(lpNewFileName));

    std::ostringstream body;
    body << "\"args\":{"
         << "\"lpExistingFileName\":\"" << Logger::JsonEscape(existingFileName) << "\","
         << "\"lpNewFileName\":\"" << Logger::JsonEscape(newFileName) << "\","
         << "\"lpProgressRoutine\":\"0x" << std::hex << lpProgressRoutine << "\","
         << "\"lpData\":\"0x" << std::hex << lpData << "\","
         << "\"pbCancel\":\"0x" << std::hex << pbCancel << "\","
         << "\"dwCopyFlags\":\"0x" << std::hex << dwCopyFlags << "\""
         << "}";

    Logger::Instance().LogFileEvent("CopyFileExA", "before", body.str(), tid);
}

VOID AfterCopyFileExA(THREADID tid, ADDRINT retValue) { LogHandleResult("CopyFileExA", retValue, tid, "return"); }

/*
    Microsoft Documentation: 
    https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-deletefilew
*/
VOID BeforeDeleteFileW(THREADID tid, ADDRINT lpFileName) {
    std::wstring fileName = ReadWideString(reinterpret_cast<const wchar_t*>(lpFileName));

    std::ostringstream body;
    body << "\"args\":{"
         << "\"lpFileName\":\"" << Logger::JsonEscape(convertWideToStr(fileName)) << "\""
         << "}";

    Logger::Instance().LogFileEvent("DeleteFileW", "before", body.str(), tid);
}

VOID AfterDeleteFileW(THREADID tid, ADDRINT retValue) { LogHandleResult("DeleteFileW", retValue, tid, "return"); }

/*
    Microsoft Documentation: 
    https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-deletefilea
*/
VOID BeforeDeleteFileA(THREADID tid, ADDRINT lpFileName) {
    std::string fileName = ReadAnsiString(reinterpret_cast<const char*>(lpFileName));

    std::ostringstream body;
    body << "\"args\":{"
         << "\"lpFileName\":\"" << Logger::JsonEscape(fileName) << "\""
         << "}";

    Logger::Instance().LogFileEvent("DeleteFileA", "before", body.str(), tid);
}

VOID AfterDeleteFileA(THREADID tid, ADDRINT retValue) { LogHandleResult("DeleteFileA", retValue, tid, "return"); }


/*
    Microsoft Documentation: 
    https://learn.microsoft.com/en-us/windows/win32/devnotes/ntreadfile
*/
VOID BeforeNtReadFile(
    THREADID tid,
    ADDRINT FileHandle,
    ADDRINT Event,
    ADDRINT ApcRoutine,
    ADDRINT ApcContext,
    ADDRINT IoStatusBlock,
    ADDRINT Buffer,
    ADDRINT Length,
    ADDRINT ByteOffset,
    ADDRINT Key) {
    std::ostringstream body;
    body << "\"args\":{"
         << "\"FileHandle\":\"0x" << std::hex << FileHandle << "\","
         << "\"Event\":\"0x" << std::hex << Event << "\","
         << "\"ApcRoutine\":\"0x" << std::hex << ApcRoutine << "\","
         << "\"ApcContext\":\"0x" << std::hex << ApcContext << "\","
         << "\"IoStatusBlock\":\"0x" << std::hex << IoStatusBlock << "\","
         << "\"Buffer\":\"0x" << std::hex << Buffer << "\","
         << "\"Length\":\"0x" << std::hex << Length << "\","
         << "\"ByteOffset\":\"0x" << std::hex << ByteOffset << "\""
         << "\"Key\":\"0x" << std::hex << Key << "\""
         << "}";

    Logger::Instance().LogFileEvent("NtReadFile", "before", body.str(), tid);
}

VOID AfterNtReadFile(THREADID tid, ADDRINT retValue) { LogHandleResult("NtReadFile", retValue, tid, "return"); }

/*
    Microsoft Documentation: 
    https://learn.microsoft.com/en-us/windows/win32/devnotes/ntreadfile
*/
VOID BeforeNtWriteFile(
    THREADID tid,
    ADDRINT FileHandle,
    ADDRINT Event,
    ADDRINT ApcRoutine,
    ADDRINT ApcContext,
    ADDRINT IoStatusBlock,
    ADDRINT Buffer,
    ADDRINT Length,
    ADDRINT ByteOffset,
    ADDRINT Key) {
    std::ostringstream body;
    body << "\"args\":{"
         << "\"FileHandle\":\"0x" << std::hex << FileHandle << "\","
         << "\"Event\":\"0x" << std::hex << Event << "\","
         << "\"ApcRoutine\":\"0x" << std::hex << ApcRoutine << "\","
         << "\"ApcContext\":\"0x" << std::hex << ApcContext << "\","
         << "\"IoStatusBlock\":\"0x" << std::hex << IoStatusBlock << "\","
         << "\"Buffer\":\"0x" << std::hex << Buffer << "\","
         << "\"Length\":\"0x" << std::hex << Length << "\","
         << "\"ByteOffset\":\"0x" << std::hex << ByteOffset << "\""
         << "\"Key\":\"0x" << std::hex << Key << "\""
         << "}";

    Logger::Instance().LogFileEvent("NtWriteFile", "before", body.str(), tid);
}

VOID AfterNtWriteFile(THREADID tid, ADDRINT retValue) { LogHandleResult("NtWriteFile", retValue, tid, "return"); }

/*
    Microsoft Documentation: 
    https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getfileattributesw
*/
VOID BeforeGetFileAttributesW(THREADID tid, ADDRINT lpFileName) {
    std::wstring fileName = ReadWideString(reinterpret_cast<const wchar_t*>(lpFileName));

    std::ostringstream body;
    body << "\"args\":{"
         << "\"lpFileName\":\"" << Logger::JsonEscape(convertWideToStr(fileName)) << "\""
         << "}";

    Logger::Instance().LogFileEvent("GetFileAttributesW", "before", body.str(), tid);
}

VOID AfterGetFileAttributesW(THREADID tid, ADDRINT retValue) { LogHandleResult("GetFileAttributesW", retValue, tid, "return"); }

/*
    Microsoft Documentation: 
    https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getfileattributesa
*/
VOID BeforeGetFileAttributesA(THREADID tid, ADDRINT lpFileName) {
    std::string fileName = ReadAnsiString(reinterpret_cast<const char*>(lpFileName));

    std::ostringstream body;
    body << "\"args\":{"
         << "\"lpFileName\":\"" << Logger::JsonEscape(fileName) << "\""
         << "}";

    Logger::Instance().LogFileEvent("GetFileAttributesA", "before", body.str(), tid);
}

VOID AfterGetFileAttributesA(THREADID tid, ADDRINT retValue) { LogHandleResult("GetFileAttributesA", retValue, tid, "return"); }

/*
    Microsoft Documentation: 
    https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getfileattributesexw
*/
VOID BeforeGetFileAttributesExW(THREADID tid, ADDRINT lpFileName, ADDRINT fInfoLevelId, ADDRINT lpFileInformation) {
    std::wstring fileName = ReadWideString(reinterpret_cast<const wchar_t*>(lpFileName));

    std::ostringstream body;
    body << "\"args\":{"
         << "\"lpFileName\":\"" << Logger::JsonEscape(convertWideToStr(fileName)) << "\","
         << "\"fInfoLevelId\":\"0x" << std::hex << fInfoLevelId << "\","
         << "\"lpFileInformation\":\"0x" << std::hex << lpFileInformation << "\""
         << "}";

    Logger::Instance().LogFileEvent("GetFileAttributesExW", "before", body.str(), tid);
}

VOID AfterGetFileAttributesExW(THREADID tid, ADDRINT retValue) { LogHandleResult("GetFileAttributesExW", retValue, tid, "return"); }

/*
    Microsoft Documentation: 
    https://learn.microsoft.com/en-us/windows/win32/api/fileapi/nf-fileapi-getfileattributesexa
*/
VOID BeforeGetFileAttributesExA(THREADID tid, ADDRINT lpFileName, ADDRINT fInfoLevelId, ADDRINT lpFileInformation) {
    std::string fileName = ReadAnsiString(reinterpret_cast<const char*>(lpFileName));

    std::ostringstream body;
    body << "\"args\":{"
         << "\"lpFileName\":\"" << Logger::JsonEscape(fileName) << "\","
         << "\"fInfoLevelId\":\"0x" << std::hex << fInfoLevelId << "\","
         << "\"lpFileInformation\":\"0x" << std::hex << lpFileInformation << "\""
         << "}";

    Logger::Instance().LogFileEvent("GetFileAttributesExA", "before", body.str(), tid);
}

VOID AfterGetFileAttributesExA(THREADID tid, ADDRINT retValue) { LogHandleResult("GetFileAttributesExA", retValue, tid, "return"); }


VOID InstrumentFileOperations(IMG img, VOID* v) {
    InstrumentRoutine(img, "CreateFileW", AFUNPTR(BeforeCreateFileW), AFUNPTR(AfterCreateFileW), 7);
    InstrumentRoutine(img, "CreateFileA", AFUNPTR(BeforeCreateFileA), AFUNPTR(AfterCreateFileA), 7);

    InstrumentRoutine(img, "FindFirstFileW", AFUNPTR(BeforeFindFirstFileW), AFUNPTR(AfterFindFirstFileW), 2);
    InstrumentRoutine(img, "FindFirstFileA", AFUNPTR(BeforeFindFirstFileA), AFUNPTR(AfterFindFirstFileA), 2);
    InstrumentRoutine(img, "FindFirstFileExW", AFUNPTR(BeforeFindFirstFileExW), AFUNPTR(AfterFindFirstFileExW), 6);
    InstrumentRoutine(img, "FindFirstFileExA", AFUNPTR(BeforeFindFirstFileExA), AFUNPTR(AfterFindFirstFileExA), 6);
    InstrumentRoutine(img, "FindNextFileW", AFUNPTR(BeforeFindNextFileW), AFUNPTR(AfterFindNextFileW), 2);
    InstrumentRoutine(img, "FindNextFileA", AFUNPTR(BeforeFindNextFileA), AFUNPTR(AfterFindNextFileA), 2);

    InstrumentRoutine(img, "ReadFile", AFUNPTR(BeforeReadFile), AFUNPTR(AfterReadFile), 5);
    InstrumentRoutine(img, "WriteFile", AFUNPTR(BeforeWriteFile), AFUNPTR(AfterWriteFile), 5);
    InstrumentRoutine(img, "SetFilePointer", AFUNPTR(BeforeSetFilePointer), AFUNPTR(AfterSetFilePointer), 4);
    InstrumentRoutine(img, "SetFilePointerEx", AFUNPTR(BeforeSetFilePointerEx), AFUNPTR(AfterSetFilePointerEx), 4);
    InstrumentRoutine(img, "GetFileSize", AFUNPTR(BeforeGetFileSize), AFUNPTR(AfterGetFileSize), 2);
    InstrumentRoutine(img, "GetFileSizeEx", AFUNPTR(BeforeGetFileSizeEx), AFUNPTR(AfterGetFileSizeEx), 2);
    InstrumentRoutine(img, "SetFileAttributesW", AFUNPTR(BeforeSetFileAttributesW), AFUNPTR(AfterSetFileAttributesW), 2);
    InstrumentRoutine(img, "SetFileAttributesA", AFUNPTR(BeforeSetFileAttributesA), AFUNPTR(AfterSetFileAttributesA), 2);
    InstrumentRoutine(img, "GetFileType", AFUNPTR(BeforeGetFileType), AFUNPTR(AfterGetFileType), 1);
    InstrumentRoutine(img, "CopyFileW", AFUNPTR(BeforeCopyFileW), AFUNPTR(AfterCopyFileW), 3);
    InstrumentRoutine(img, "CopyFileA", AFUNPTR(BeforeCopyFileA), AFUNPTR(AfterCopyFileA), 3);
    InstrumentRoutine(img, "CopyFileExW", AFUNPTR(BeforeCopyFileExW), AFUNPTR(AfterCopyFileExW), 6);
    InstrumentRoutine(img, "CopyFileExA", AFUNPTR(BeforeCopyFileExA), AFUNPTR(AfterCopyFileExA), 6);
    InstrumentRoutine(img, "DeleteFileW", AFUNPTR(BeforeDeleteFileW), AFUNPTR(AfterDeleteFileW), 1);
    InstrumentRoutine(img, "DeleteFileA", AFUNPTR(BeforeDeleteFileA), AFUNPTR(AfterDeleteFileA), 1);
    InstrumentRoutine(img, "NtReadFile", AFUNPTR(BeforeNtReadFile), AFUNPTR(AfterNtReadFile), 9);
    InstrumentRoutine(img, "NtWriteFile", AFUNPTR(BeforeNtWriteFile), AFUNPTR(AfterNtWriteFile), 9);
    InstrumentRoutine(img, "GetFileAttributesW", AFUNPTR(BeforeGetFileAttributesW), AFUNPTR(AfterGetFileAttributesW), 1);
    InstrumentRoutine(img, "GetFileAttributesA", AFUNPTR(BeforeGetFileAttributesA), AFUNPTR(AfterGetFileAttributesA), 1);
    InstrumentRoutine(img, "GetFileAttributesExW", AFUNPTR(BeforeGetFileAttributesExW), AFUNPTR(AfterGetFileAttributesExW), 3);
    InstrumentRoutine(img, "GetFileAttributesExA", AFUNPTR(BeforeGetFileAttributesExA), AFUNPTR(AfterGetFileAttributesExA), 3);
}

void StartFileOperationsModule() {
    IMG_AddInstrumentFunction(InstrumentFileOperations, 0);
}

void FinishFileOperationsModule() {
    Logger::Instance().LogMain("File operations module stopping -> Check FileOperations.jsonl for file-specific Windows APIs");
}
