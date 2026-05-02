#pragma once

#include "pin.H"
#include "logger.h"
#include <sstream>
#include <string>
#include "utils.h"

void LogHandleResult(const std::string& api, ADDRINT retValue, THREADID tid, const char* fieldName = "handle");

VOID BeforeCreateFileW(
    THREADID tid,
    ADDRINT lpFileName,
    ADDRINT dwDesiredAccess,
    ADDRINT dwShareMode,
    ADDRINT lpSecurityAttributes,
    ADDRINT dwCreationDisposition,
    ADDRINT dwFlagsAndAttributes,
    ADDRINT hTemplateFile);
VOID AfterCreateFileW(THREADID tid, ADDRINT retHandle);

VOID BeforeCreateFileA(
    THREADID tid,
    ADDRINT lpFileName,
    ADDRINT dwDesiredAccess,
    ADDRINT dwShareMode,
    ADDRINT lpSecurityAttributes,
    ADDRINT dwCreationDisposition,
    ADDRINT dwFlagsAndAttributes,
    ADDRINT hTemplateFile);
VOID AfterCreateFileA(THREADID tid, ADDRINT retHandle);

VOID BeforeFindFirstFileW(THREADID tid, ADDRINT lpFileName, ADDRINT lpFindFileData);
VOID AfterFindFirstFileW(THREADID tid, ADDRINT retHandle);
VOID BeforeFindFirstFileA(THREADID tid, ADDRINT lpFileName, ADDRINT lpFindFileData);
VOID AfterFindFirstFileA(THREADID tid, ADDRINT retHandle);

VOID BeforeFindFirstFileExW(
    THREADID tid,
    ADDRINT lpFileName,
    ADDRINT fInfoLevelId,
    ADDRINT lpFindFileData,
    ADDRINT fSearchOp,
    ADDRINT lpSearchFilter,
    ADDRINT dwAdditionalFlags);
VOID AfterFindFirstFileExW(THREADID tid, ADDRINT retHandle);
VOID BeforeFindFirstFileExA(
    THREADID tid,
    ADDRINT lpFileName,
    ADDRINT fInfoLevelId,
    ADDRINT lpFindFileData,
    ADDRINT fSearchOp,
    ADDRINT lpSearchFilter,
    ADDRINT dwAdditionalFlags);
VOID AfterFindFirstFileExA(THREADID tid, ADDRINT retHandle);

VOID BeforeFindNextFileW(THREADID tid, ADDRINT hFindFile, ADDRINT lpFindFileData);
VOID AfterFindNextFileW(THREADID tid, ADDRINT retValue);
VOID BeforeFindNextFileA(THREADID tid, ADDRINT hFindFile, ADDRINT lpFindFileData);
VOID AfterFindNextFileA(THREADID tid, ADDRINT retValue);

VOID BeforeReadFile(THREADID tid, ADDRINT hFile, ADDRINT lpBuffer, ADDRINT nNumberOfBytesToRead, ADDRINT lpNumberOfBytesRead, ADDRINT lpOverlapped);
VOID AfterReadFile(THREADID tid, ADDRINT retValue);

VOID BeforeWriteFile(THREADID tid, ADDRINT hFile, ADDRINT lpBuffer, ADDRINT nNumberOfBytesToWrite, ADDRINT lpNumberOfBytesWritten, ADDRINT lpOverlapped);
VOID AfterWriteFile(THREADID tid, ADDRINT retValue);

VOID BeforeSetFilePointer(THREADID tid, ADDRINT hFile, ADDRINT lDistanceToMove, ADDRINT lpDistanceToMoveHigh, ADDRINT dwMoveMethod);
VOID AfterSetFilePointer(THREADID tid, ADDRINT retValue);

VOID BeforeSetFilePointerEx(THREADID tid, ADDRINT hFile, ADDRINT liDistanceToMove, ADDRINT lpNewFilePointer, ADDRINT dwMoveMethod);
VOID AfterSetFilePointerEx(THREADID tid, ADDRINT retValue);

VOID BeforeGetFileSize(THREADID tid, ADDRINT hFile, ADDRINT lpFileSizeHigh);
VOID AfterGetFileSize(THREADID tid, ADDRINT retValue);

VOID BeforeGetFileSizeEx(THREADID tid, ADDRINT hFile, ADDRINT lpFileSize);
VOID AfterGetFileSizeEx(THREADID tid, ADDRINT retValue);

VOID BeforeGetFileType(THREADID tid, ADDRINT hFile);
VOID AfterGetFileType(THREADID tid, ADDRINT retValue);

VOID BeforeSetFileAttributesW(THREADID tid, ADDRINT lpFileName, ADDRINT dwFileAttributes);
VOID AfterSetFileAttributesW(THREADID tid, ADDRINT retValue);
VOID BeforeSetFileAttributesA(THREADID tid, ADDRINT lpFileName, ADDRINT dwFileAttributes);
VOID AfterSetFileAttributesA(THREADID tid, ADDRINT retValue);


VOID BeforeCopyFileW(THREADID tid, ADDRINT lpExistingFileName, ADDRINT lpNewFileName, ADDRINT bFailIfExists);
VOID AfterCopyFileW(THREADID tid, ADDRINT retValue);
VOID BeforeCopyFileA(THREADID tid, ADDRINT lpExistingFileName, ADDRINT lpNewFileName, ADDRINT bFailIfExists);
VOID AfterCopyFileA(THREADID tid, ADDRINT retValue);

VOID BeforeCopyFileExW(
    THREADID tid,
    ADDRINT lpExistingFileName,
    ADDRINT lpNewFileName,
    ADDRINT lpProgressRoutine,
    ADDRINT lpData,
    ADDRINT pbCancel,
    ADDRINT dwCopyFlags);
VOID AfterCopyFileExW(THREADID tid, ADDRINT retValue);
VOID BeforeCopyFileExA(
    THREADID tid,
    ADDRINT lpExistingFileName,
    ADDRINT lpNewFileName,
    ADDRINT lpProgressRoutine,
    ADDRINT lpData,
    ADDRINT pbCancel,
    ADDRINT dwCopyFlags);
VOID AfterCopyFileExA(THREADID tid, ADDRINT retValue);

VOID BeforeDeleteFileW(THREADID tid, ADDRINT lpFileName);
VOID AfterDeleteFileW(THREADID tid, ADDRINT retValue);
VOID BeforeDeleteFileA(THREADID tid, ADDRINT lpFileName);
VOID AfterDeleteFileA(THREADID tid, ADDRINT retValue);

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
    ADDRINT Key);
VOID AfterNtReadFile(THREADID tid, ADDRINT retValue);

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
    ADDRINT Key);
VOID AfterNtWriteFile(THREADID tid, ADDRINT retValue);

VOID BeforeGetFileAttributesW(THREADID tid, ADDRINT lpFileName);
VOID AfterGetFileAttributesW(THREADID tid, ADDRINT retValue);
VOID BeforeGetFileAttributesA(THREADID tid, ADDRINT lpFileName);
VOID AfterGetFileAttributesA(THREADID tid, ADDRINT retValue);
VOID BeforeGetFileAttributesExW(THREADID tid, ADDRINT lpFileName, ADDRINT fInfoLevelId, ADDRINT lpFileInformation);
VOID AfterGetFileAttributesExW(THREADID tid, ADDRINT retValue);
VOID BeforeGetFileAttributesExA(THREADID tid, ADDRINT lpFileName, ADDRINT fInfoLevelId, ADDRINT lpFileInformation);
VOID AfterGetFileAttributesExA(THREADID tid, ADDRINT retValue);

void InstrumentRoutine(IMG img, const char* apiName, AFUNPTR beforeFunction, AFUNPTR afterFunction, UINT32 argCount);
VOID InstrumentFileOperations(IMG img, VOID* v);

void StartFileOperationsModule();
void FinishFileOperationsModule();
