#pragma once

#include "pin.H"
#include "logger.h"
#include <sstream>
#include <string>
#include "utils.h"

void LogZeroResultRegistry(const std::string& api, ADDRINT retValue, THREADID tid, const char* fieldName);

VOID BeforeRegOpenKeyExW(THREADID tid, ADDRINT hKey, ADDRINT lpSubKey, ADDRINT ulOptions, ADDRINT samDesired, ADDRINT phkResult);
VOID AfterRegOpenKeyExW(THREADID tid, ADDRINT retValue);

VOID BeforeRegOpenKeyExA(THREADID tid, ADDRINT hKey, ADDRINT lpSubKey, ADDRINT ulOptions, ADDRINT samDesired, ADDRINT phkResult);
VOID AfterRegOpenKeyExA(THREADID tid, ADDRINT retValue);

VOID BeforeRegCreateKeyExW(THREADID tid, ADDRINT hKey, ADDRINT lpSubKey, ADDRINT Reserved, ADDRINT lpClass, ADDRINT dwOptions, ADDRINT samDesired, ADDRINT lpSecurityAttributes, ADDRINT phkResult, ADDRINT lpdwDisposition);
VOID AfterRegCreateKeyExW(THREADID tid, ADDRINT retValue);

VOID BeforeRegCreateKeyExA(THREADID tid, ADDRINT hKey, ADDRINT lpSubKey, ADDRINT Reserved, ADDRINT lpClass, ADDRINT dwOptions, ADDRINT samDesired, ADDRINT lpSecurityAttributes, ADDRINT phkResult, ADDRINT lpdwDisposition);
VOID AfterRegCreateKeyExA(THREADID tid, ADDRINT retValue);

VOID BeforeRegSetValueExW(THREADID tid, ADDRINT hKey, ADDRINT lpValueName, ADDRINT Reserved, ADDRINT dwType, ADDRINT lpData, ADDRINT cbData);
VOID AfterRegSetValueExW(THREADID tid, ADDRINT retValue);

VOID BeforeRegSetValueExA(THREADID tid, ADDRINT hKey, ADDRINT lpValueName, ADDRINT Reserved, ADDRINT dwType, ADDRINT lpData, ADDRINT cbData);
VOID AfterRegSetValueExA(THREADID tid, ADDRINT retValue);

VOID BeforeRegQueryValueExW(THREADID tid, ADDRINT hKey, ADDRINT lpValueName, ADDRINT lpReserved, ADDRINT lpType, ADDRINT lpData, ADDRINT lpcbData);
VOID AfterRegQueryValueExW(THREADID tid, ADDRINT retValue);

VOID BeforeRegQueryValueExA(THREADID tid, ADDRINT hKey, ADDRINT lpValueName, ADDRINT lpReserved, ADDRINT lpType, ADDRINT lpData, ADDRINT lpcbData);
VOID AfterRegQueryValueExA(THREADID tid, ADDRINT retValue);

VOID BeforeRegDeleteKeyW(THREADID tid, ADDRINT hKey, ADDRINT lpSubKey);
VOID AfterRegDeleteKeyW(THREADID tid, ADDRINT retValue);

VOID BeforeRegDeleteKeyA(THREADID tid, ADDRINT hKey, ADDRINT lpSubKey);
VOID AfterRegDeleteKeyA(THREADID tid, ADDRINT retValue);

VOID BeforeRegDeleteValueW(THREADID tid, ADDRINT hKey, ADDRINT lpValueName);
VOID AfterRegDeleteValueW(THREADID tid, ADDRINT retValue);

VOID BeforeRegDeleteValueA(THREADID tid, ADDRINT hKey, ADDRINT lpValueName);
VOID AfterRegDeleteValueA(THREADID tid, ADDRINT retValue);

VOID BeforeRegEnumKeyExW(THREADID tid, ADDRINT hKey, ADDRINT dwIndex, ADDRINT lpName, ADDRINT lpcchName, ADDRINT lpReserved, ADDRINT lpClass, ADDRINT lpcchClass, ADDRINT lpftLastWriteTime);
VOID AfterRegEnumKeyExW(THREADID tid, ADDRINT retValue);

VOID BeforeRegEnumKeyExA(THREADID tid, ADDRINT hKey, ADDRINT dwIndex, ADDRINT lpName, ADDRINT lpcchName, ADDRINT lpReserved, ADDRINT lpClass, ADDRINT lpcchClass, ADDRINT lpftLastWriteTime);
VOID AfterRegEnumKeyExA(THREADID tid, ADDRINT retValue);

VOID BeforeRegEnumValueW(THREADID tid, ADDRINT hKey, ADDRINT dwIndex, ADDRINT lpValueName, ADDRINT lpcchValueName, ADDRINT lpReserved, ADDRINT lpType, ADDRINT lpData, ADDRINT lpcbData);
VOID AfterRegEnumValueW(THREADID tid, ADDRINT retValue);

VOID BeforeRegEnumValueA(THREADID tid, ADDRINT hKey, ADDRINT dwIndex, ADDRINT lpValueName, ADDRINT lpcchValueName, ADDRINT lpReserved, ADDRINT lpType, ADDRINT lpData, ADDRINT lpcbData);
VOID AfterRegEnumValueA(THREADID tid, ADDRINT retValue);

VOID BeforeRegCloseKey(THREADID tid, ADDRINT hKey);
VOID AfterRegCloseKey(THREADID tid, ADDRINT retValue);

VOID BeforeNtOpenKey(THREADID tid, ADDRINT KeyHandle, ADDRINT DesiredAccess, ADDRINT ObjectAttributes);
VOID AfterNtOpenKey(THREADID tid, ADDRINT retValue);

VOID BeforeNtCreateKey(THREADID tid, ADDRINT KeyHandle, ADDRINT DesiredAccess, ADDRINT ObjectAttributes, ADDRINT TitleIndex, ADDRINT Class, ADDRINT CreateOptions, ADDRINT Disposition);
VOID AfterNtCreateKey(THREADID tid, ADDRINT retValue);

VOID BeforeNtSetValueKey(THREADID tid, ADDRINT KeyHandle, ADDRINT ValueName, ADDRINT TitleIndex, ADDRINT Type, ADDRINT Data, ADDRINT DataSize);
VOID AfterNtSetValueKey(THREADID tid, ADDRINT retValue);

VOID BeforeNtDeleteValueKey(THREADID tid, ADDRINT KeyHandle, ADDRINT ValueName);
VOID AfterNtDeleteValueKey(THREADID tid, ADDRINT retValue);

VOID InstrumentRegistryOperations(IMG img, VOID* v);


void StartRegistryOperationsModule();
void FinishRegistryOperationsModule();