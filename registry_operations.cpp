#include "registry_operations.h"

void LogZeroResultRegistry(const std::string& api, ADDRINT retValue, THREADID tid, const char* fieldName) {
    std::ostringstream body;
    body << "\"result\":{"
         << "\"" << fieldName << "\":\"0x" << std::hex << retValue << "\"," 
         << "\"success\":" << ((retValue == 0) ? "true" : "false")
         << "}";
    Logger::Instance().LogRegistryEvent(api, "after", body.str(), tid);
}

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regopenkeyexw
*/
VOID BeforeRegOpenKeyExW(THREADID tid, ADDRINT hKey, ADDRINT lpSubKey, ADDRINT ulOptions, ADDRINT samDesired, ADDRINT phkResult) {
    std::wstring subKey = ReadWideString(reinterpret_cast<const wchar_t*>(lpSubKey));
    
    std::ostringstream body;
    body << "\"args\":{"
         << "\"hKey\":\"0x" << std::hex << hKey << "\","
         << "\"lpSubKey\":\"" << Logger::JsonEscape(convertWideToStr(subKey)) << "\","
         << "\"ulOptions\":\"0x" << std::hex << ulOptions << "\","
         << "\"samDesired\":\"0x" << std::hex << samDesired << "\","
         << "\"phkResult\":\"0x" << std::hex << phkResult << "\""
         << "}";

    Logger::Instance().LogRegistryEvent("RegOpenKeyExW", "before", body.str(), tid);
}

VOID AfterRegOpenKeyExW(THREADID tid, ADDRINT retValue) { LogZeroResultRegistry("RegOpenKeyExW", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regopenkeyexa
*/
VOID BeforeRegOpenKeyExA(THREADID tid, ADDRINT hKey, ADDRINT lpSubKey, ADDRINT ulOptions, ADDRINT samDesired, ADDRINT phkResult) {
    std::string subKey = ReadAnsiString(reinterpret_cast<const char*>(lpSubKey));

    std::ostringstream body;
    body << "\"args\":{"
         << "\"hKey\":\"0x" << std::hex << hKey << "\","
         << "\"lpSubKey\":\"" << Logger::JsonEscape(subKey) << "\","
         << "\"ulOptions\":\"0x" << std::hex << ulOptions << "\","
         << "\"samDesired\":\"0x" << std::hex << samDesired << "\","
         << "\"phkResult\":\"0x" << std::hex << phkResult << "\""
         << "}";

    Logger::Instance().LogRegistryEvent("RegOpenKeyExA", "before", body.str(), tid);
}

VOID AfterRegOpenKeyExA(THREADID tid, ADDRINT retValue) { LogZeroResultRegistry("RegOpenKeyExA", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regcreatekeyexw
*/
VOID BeforeRegCreateKeyExW(THREADID tid, ADDRINT hKey, ADDRINT lpSubKey, ADDRINT Reserved, ADDRINT lpClass, ADDRINT dwOptions, ADDRINT samDesired, ADDRINT lpSecurityAttributes, ADDRINT phkResult, ADDRINT lpdwDisposition) {
    std::wstring subKey = ReadWideString(reinterpret_cast<const wchar_t*>(lpSubKey));
    std::wstring classLp = ReadWideString(reinterpret_cast<const wchar_t*>(lpClass));

    std::ostringstream body;
    body << "\"args\":{"
         << "\"hKey\":\"0x" << std::hex << hKey << "\","
         << "\"lpSubKey\":\"" << Logger::JsonEscape(convertWideToStr(subKey)) << "\","
         << "\"Reserved\":\"0x" << std::hex << Reserved << "\","
         << "\"lpClass\":\"" << Logger::JsonEscape(convertWideToStr(classLp)) << "\","
         << "\"dwOptions\":\"0x" << std::hex << dwOptions << "\","
         << "\"samDesired\":\"0x" << std::hex << samDesired << "\","
         << "\"lpSecurityAttributes\":\"0x" << std::hex << lpSecurityAttributes << "\","
         << "\"phkResult\":\"0x" << std::hex << phkResult << "\","
         << "\"lpdwDisposition\":\"0x" << std::hex << lpdwDisposition << "\""
         << "}";

    Logger::Instance().LogRegistryEvent("RegCreateKeyExW", "before", body.str(), tid);
}

VOID AfterRegCreateKeyExW(THREADID tid, ADDRINT retValue) { LogZeroResultRegistry("RegCreateKeyExW", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regcreatekeyexa
*/
VOID BeforeRegCreateKeyExA(THREADID tid, ADDRINT hKey, ADDRINT lpSubKey, ADDRINT Reserved, ADDRINT lpClass, ADDRINT dwOptions, ADDRINT samDesired, ADDRINT lpSecurityAttributes, ADDRINT phkResult, ADDRINT lpdwDisposition) {
    std::string subKey = ReadAnsiString(reinterpret_cast<const char*>(lpSubKey));
    std::string classLp = ReadAnsiString(reinterpret_cast<const char*>(lpClass));

    std::ostringstream body;
    body << "\"args\":{"
         << "\"hKey\":\"0x" << std::hex << hKey << "\","
         << "\"lpSubKey\":\"" << Logger::JsonEscape(subKey) << "\","
         << "\"Reserved\":\"0x" << std::hex << Reserved << "\","
         << "\"lpClass\":\"" << Logger::JsonEscape(classLp) << "\","
         << "\"dwOptions\":\"0x" << std::hex << dwOptions << "\","
         << "\"samDesired\":\"0x" << std::hex << samDesired << "\","
         << "\"lpSecurityAttributes\":\"0x" << std::hex << lpSecurityAttributes << "\","
         << "\"phkResult\":\"0x" << std::hex << phkResult << "\","
         << "\"lpdwDisposition\":\"0x" << std::hex << lpdwDisposition << "\""
         << "}";

    Logger::Instance().LogRegistryEvent("RegCreateKeyExA", "before", body.str(), tid);
}

VOID AfterRegCreateKeyExA(THREADID tid, ADDRINT retValue) { LogZeroResultRegistry("RegCreateKeyExA", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regsetvalueexw
*/
VOID BeforeRegSetValueExW(THREADID tid, ADDRINT hKey, ADDRINT lpValueName, ADDRINT Reserved, ADDRINT dwType, ADDRINT lpData, ADDRINT cbData) {
    std::wstring valueName = ReadWideString(reinterpret_cast<const wchar_t*>(lpValueName));

    std::ostringstream body;
    body << "\"args\":{"
         << "\"hKey\":\"0x" << std::hex << hKey << "\","
         << "\"lpValueName\":\"" << Logger::JsonEscape(convertWideToStr(valueName)) << "\","
         << "\"Reserved\":\"0x" << std::hex << Reserved << "\","
         << "\"dwType\":\"0x" << std::hex << dwType << "\","
         << "\"lpData\":\"0x" << std::hex << lpData << "\","
         << "\"cbData\":\"0x" << std::hex << cbData << "\""
         << "}";

    Logger::Instance().LogRegistryEvent("RegSetValueExW", "before", body.str(), tid);
}

VOID AfterRegSetValueExW(THREADID tid, ADDRINT retValue) { LogZeroResultRegistry("RegSetValueExW", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regsetvalueexa
*/
VOID BeforeRegSetValueExA(THREADID tid, ADDRINT hKey, ADDRINT lpValueName, ADDRINT Reserved, ADDRINT dwType, ADDRINT lpData, ADDRINT cbData) {
    std::string valueName = ReadAnsiString(reinterpret_cast<const char*>(lpValueName));

    std::ostringstream body;
    body << "\"args\":{"
         << "\"hKey\":\"0x" << std::hex << hKey << "\","
         << "\"lpValueName\":\"" << Logger::JsonEscape(valueName) << "\","
         << "\"Reserved\":\"0x" << std::hex << Reserved << "\","
         << "\"dwType\":\"0x" << std::hex << dwType << "\","
         << "\"lpData\":\"0x" << std::hex << lpData << "\","
         << "\"cbData\":\"0x" << std::hex << cbData << "\""
         << "}";

    Logger::Instance().LogRegistryEvent("RegSetValueExA", "before", body.str(), tid);
}

VOID AfterRegSetValueExA(THREADID tid, ADDRINT retValue) { LogZeroResultRegistry("RegSetValueExA", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regqueryvalueexw
*/
VOID BeforeRegQueryValueExW(THREADID tid, ADDRINT hKey, ADDRINT lpValueName, ADDRINT lpReserved, ADDRINT lpType, ADDRINT lpData, ADDRINT lpcbData) {
    std::wstring valueName = ReadWideString(reinterpret_cast<const wchar_t*>(lpValueName));

    std::ostringstream body;
    body << "\"args\":{"
         << "\"hKey\":\"0x" << std::hex << hKey << "\","
         << "\"lpValueName\":\"" << Logger::JsonEscape(convertWideToStr(valueName)) << "\","
         << "\"lpReserved\":\"0x" << std::hex << lpReserved << "\","
         << "\"lpType\":\"0x" << std::hex << lpType << "\","
         << "\"lpData\":\"0x" << std::hex << lpData << "\","
         << "\"lpcbData\":\"0x" << std::hex << lpcbData << "\""
         << "}";

    Logger::Instance().LogRegistryEvent("RegQueryValueExW", "before", body.str(), tid);
}

VOID AfterRegQueryValueExW(THREADID tid, ADDRINT retValue) { LogZeroResultRegistry("RegQueryValueExW", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regqueryvalueexa
*/
VOID BeforeRegQueryValueExA(THREADID tid, ADDRINT hKey, ADDRINT lpValueName, ADDRINT lpReserved, ADDRINT lpType, ADDRINT lpData, ADDRINT lpcbData) {
    std::string valueName = ReadAnsiString(reinterpret_cast<const char*>(lpValueName));

    std::ostringstream body;
    body << "\"args\":{"
         << "\"hKey\":\"0x" << std::hex << hKey << "\","
         << "\"lpValueName\":\"" << Logger::JsonEscape(valueName) << "\","
         << "\"lpReserved\":\"0x" << std::hex << lpReserved << "\","
         << "\"lpType\":\"0x" << std::hex << lpType << "\","
         << "\"lpData\":\"0x" << std::hex << lpData << "\","
         << "\"lpcbData\":\"0x" << std::hex << lpcbData << "\""
         << "}";

    Logger::Instance().LogRegistryEvent("RegQueryValueExA", "before", body.str(), tid);
}

VOID AfterRegQueryValueExA(THREADID tid, ADDRINT retValue) { LogZeroResultRegistry("RegQueryValueExA", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regdeletekeyw
*/
VOID BeforeRegDeleteKeyW(THREADID tid, ADDRINT hKey, ADDRINT lpSubKey) {
    std::wstring subKey = ReadWideString(reinterpret_cast<const wchar_t*>(lpSubKey));

    std::ostringstream body;
    body << "\"args\":{"
         << "\"hKey\":\"0x" << std::hex << hKey << "\","
         << "\"lpSubKey\":\"" << Logger::JsonEscape(convertWideToStr(subKey)) << "\""
         << "}";

    Logger::Instance().LogRegistryEvent("RegDeleteKeyW", "before", body.str(), tid);
}

VOID AfterRegDeleteKeyW(THREADID tid, ADDRINT retValue) { LogZeroResultRegistry("RegDeleteKeyW", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regdeletekeya
*/
VOID BeforeRegDeleteKeyA(THREADID tid, ADDRINT hKey, ADDRINT lpSubKey) {
    std::string subKey = ReadAnsiString(reinterpret_cast<const char*>(lpSubKey));

    std::ostringstream body;
    body << "\"args\":{"
         << "\"hKey\":\"0x" << std::hex << hKey << "\","
         << "\"lpSubKey\":\"" << Logger::JsonEscape(subKey) << "\""
         << "}";

    Logger::Instance().LogRegistryEvent("RegDeleteKeyA", "before", body.str(), tid);
}

VOID AfterRegDeleteKeyA(THREADID tid, ADDRINT retValue) { LogZeroResultRegistry("RegDeleteKeyA", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regdeletevaluew
*/
VOID BeforeRegDeleteValueW(THREADID tid, ADDRINT hKey, ADDRINT lpValueName) {
    std::wstring valueName = ReadWideString(reinterpret_cast<const wchar_t*>(lpValueName));

    std::ostringstream body;
    body << "\"args\":{"
         << "\"hKey\":\"0x" << std::hex << hKey << "\","
         << "\"lpValueName\":\"" << Logger::JsonEscape(convertWideToStr(valueName)) << "\""
         << "}";

    Logger::Instance().LogRegistryEvent("RegDeleteValueW", "before", body.str(), tid);
}

VOID AfterRegDeleteValueW(THREADID tid, ADDRINT retValue) { LogZeroResultRegistry("RegDeleteValueW", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regdeletevaluea
*/
VOID BeforeRegDeleteValueA(THREADID tid, ADDRINT hKey, ADDRINT lpValueName) {
    std::string valueName = ReadAnsiString(reinterpret_cast<const char*>(lpValueName));

    std::ostringstream body;
    body << "\"args\":{"
         << "\"hKey\":\"0x" << std::hex << hKey << "\","
         << "\"lpValueName\":\"" << Logger::JsonEscape(valueName) << "\""
         << "}";

    Logger::Instance().LogRegistryEvent("RegDeleteValueA", "before", body.str(), tid);
}

VOID AfterRegDeleteValueA(THREADID tid, ADDRINT retValue) { LogZeroResultRegistry("RegDeleteValueA", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regenumkeyexw
    ReadWideString not used because it is LPWSTR not LPCWSTR, and it may be an empty buffer
*/
VOID BeforeRegEnumKeyExW(THREADID tid, ADDRINT hKey, ADDRINT dwIndex, ADDRINT lpName, ADDRINT lpcchName, ADDRINT lpReserved, ADDRINT lpClass, ADDRINT lpcchClass, ADDRINT lpftLastWriteTime) {
    std::ostringstream body;
    body << "\"args\":{"
         << "\"hKey\":\"0x" << std::hex << hKey << "\","
         << "\"dwIndex\":\"0x" << std::hex << dwIndex << "\","
         << "\"lpName\":\"0x" << std::hex << lpName << "\","
         << "\"lpcchName\":\"0x" << std::hex << lpcchName << "\","
         << "\"lpReserved\":\"0x" << std::hex << lpReserved << "\","
         << "\"lpClass\":\"0x" << std::hex << lpClass << "\","
         << "\"lpcchClass\":\"0x" << std::hex << lpcchClass << "\","
         << "\"lpftLastWriteTime\":\"0x" << std::hex << lpftLastWriteTime << "\""
         << "}";

    Logger::Instance().LogRegistryEvent("RegEnumKeyExW", "before", body.str(), tid);
}

VOID AfterRegEnumKeyExW(THREADID tid, ADDRINT retValue) { LogZeroResultRegistry("RegEnumKeyExW", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regenumkeyexa
    Same as above, ReadAnsiString not used
*/
VOID BeforeRegEnumKeyExA(THREADID tid, ADDRINT hKey, ADDRINT dwIndex, ADDRINT lpName, ADDRINT lpcchName, ADDRINT lpReserved, ADDRINT lpClass, ADDRINT lpcchClass, ADDRINT lpftLastWriteTime) {
    std::ostringstream body;
    body << "\"args\":{"
         << "\"hKey\":\"0x" << std::hex << hKey << "\","
         << "\"dwIndex\":\"0x" << std::hex << dwIndex << "\","
         << "\"lpName\":\"0x" << std::hex << lpName << "\","
         << "\"lpcchName\":\"0x" << std::hex << lpcchName << "\","
         << "\"lpReserved\":\"0x" << std::hex << lpReserved << "\","
         << "\"lpClass\":\"0x" << std::hex << lpClass << "\","
         << "\"lpcchClass\":\"0x" << std::hex << lpcchClass << "\","
         << "\"lpftLastWriteTime\":\"0x" << std::hex << lpftLastWriteTime << "\""
         << "}";

    Logger::Instance().LogRegistryEvent("RegEnumKeyExA", "before", body.str(), tid);
}

VOID AfterRegEnumKeyExA(THREADID tid, ADDRINT retValue) { LogZeroResultRegistry("RegEnumKeyExA", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regenumvaluew
    Same as above, ReadWideString not used
*/
VOID BeforeRegEnumValueW(THREADID tid, ADDRINT hKey, ADDRINT dwIndex, ADDRINT lpValueName, ADDRINT lpcchValueName, ADDRINT lpReserved, ADDRINT lpType, ADDRINT lpData, ADDRINT lpcbData) {
    std::ostringstream body;
    body << "\"args\":{"
         << "\"hKey\":\"0x" << std::hex << hKey << "\","
         << "\"dwIndex\":\"0x" << std::hex << dwIndex << "\","
         << "\"lpValueName\":\"0x" << std::hex << lpValueName << "\","
         << "\"lpcchValueName\":\"0x" << std::hex << lpcchValueName << "\","
         << "\"lpReserved\":\"0x" << std::hex << lpReserved << "\","
         << "\"lpType\":\"0x" << std::hex << lpType << "\","
         << "\"lpData\":\"0x" << std::hex << lpData << "\","
         << "\"lpcbData\":\"0x" << std::hex << lpcbData << "\""
         << "}";

    Logger::Instance().LogRegistryEvent("RegEnumValueW", "before", body.str(), tid);
}

VOID AfterRegEnumValueW(THREADID tid, ADDRINT retValue) { LogZeroResultRegistry("RegEnumValueW", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regenumvaluea
*/
VOID BeforeRegEnumValueA(THREADID tid, ADDRINT hKey, ADDRINT dwIndex, ADDRINT lpValueName, ADDRINT lpcchValueName, ADDRINT lpReserved, ADDRINT lpType, ADDRINT lpData, ADDRINT lpcbData) {
    std::ostringstream body;
    body << "\"args\":{"
         << "\"hKey\":\"0x" << std::hex << hKey << "\","
         << "\"dwIndex\":\"0x" << std::hex << dwIndex << "\","
         << "\"lpValueName\":\"0x" << std::hex << lpValueName << "\","
         << "\"lpcchValueName\":\"0x" << std::hex << lpcchValueName << "\","
         << "\"lpReserved\":\"0x" << std::hex << lpReserved << "\","
         << "\"lpType\":\"0x" << std::hex << lpType << "\","
         << "\"lpData\":\"0x" << std::hex << lpData << "\","
         << "\"lpcbData\":\"0x" << std::hex << lpcbData << "\""
         << "}";

    Logger::Instance().LogRegistryEvent("RegEnumValueA", "before", body.str(), tid);
}

VOID AfterRegEnumValueA(THREADID tid, ADDRINT retValue) { LogZeroResultRegistry("RegEnumValueA", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/winreg/nf-winreg-regclosekey
*/
VOID BeforeRegCloseKey(THREADID tid, ADDRINT hKey) {
    std::ostringstream body;
    body << "\"args\":{"
         << "\"hKey\":\"0x" << std::hex << hKey << "\""
         << "}";

    Logger::Instance().LogRegistryEvent("RegCloseKey", "before", body.str(), tid);
}

VOID AfterRegCloseKey(THREADID tid, ADDRINT retValue) { LogZeroResultRegistry("RegCloseKey", retValue, tid, "return"); }

/*
    Documentation (not Microsoft):
    https://ntdoc.m417z.com/ntopenkey
*/
VOID BeforeNtOpenKey(THREADID tid, ADDRINT KeyHandle, ADDRINT DesiredAccess, ADDRINT ObjectAttributes) {
    std::ostringstream body;
    body << "\"args\":{"
         << "\"KeyHandle\":\"0x" << std::hex << KeyHandle << "\","
         << "\"DesiredAccess\":\"0x" << std::hex << DesiredAccess << "\","
         << "\"ObjectAttributes\":\"0x" << std::hex << ObjectAttributes << "\""
         << "}";

    Logger::Instance().LogRegistryEvent("NtOpenKey", "before", body.str(), tid);
}

VOID AfterNtOpenKey(THREADID tid, ADDRINT retValue) { LogZeroResultRegistry("NtOpenKey", retValue, tid, "return"); }

/*
    Documentation (not Microsoft):
    https://ntdoc.m417z.com/ntcreatekey
*/
VOID BeforeNtCreateKey(THREADID tid, ADDRINT KeyHandle, ADDRINT DesiredAccess, ADDRINT ObjectAttributes, ADDRINT TitleIndex, ADDRINT Class, ADDRINT CreateOptions, ADDRINT Disposition) {
    std::ostringstream body;
    body << "\"args\":{"
         << "\"KeyHandle\":\"0x" << std::hex << KeyHandle << "\","
         << "\"DesiredAccess\":\"0x" << std::hex << DesiredAccess << "\","
         << "\"ObjectAttributes\":\"0x" << std::hex << ObjectAttributes << "\","
         << "\"TitleIndex\":\"0x" << std::hex << TitleIndex << "\","
         << "\"Class\":\"0x" << std::hex << Class << "\","
         << "\"CreateOptions\":\"0x" << std::hex << CreateOptions << "\","
         << "\"Disposition\":\"0x" << std::hex << Disposition << "\""
         << "}";

    Logger::Instance().LogRegistryEvent("NtCreateKey", "before", body.str(), tid);
}

VOID AfterNtCreateKey(THREADID tid, ADDRINT retValue) { LogZeroResultRegistry("NtCreateKey", retValue, tid, "return"); }

/*
    Documentation (not Microsoft):
    https://ntdoc.m417z.com/ntsetvaluekey
*/
VOID BeforeNtSetValueKey(THREADID tid, ADDRINT KeyHandle, ADDRINT ValueName, ADDRINT TitleIndex, ADDRINT Type, ADDRINT Data, ADDRINT DataSize) {
    std::ostringstream body;
    body << "\"args\":{"
         << "\"KeyHandle\":\"0x" << std::hex << KeyHandle << "\","
         << "\"ValueName\":\"0x" << std::hex << ValueName << "\","
         << "\"TitleIndex\":\"0x" << std::hex << TitleIndex << "\","
         << "\"Type\":\"0x" << std::hex << Type << "\","
         << "\"Data\":\"0x" << std::hex << Data << "\","
         << "\"DataSize\":\"0x" << std::hex << DataSize << "\""
         << "}";

    Logger::Instance().LogRegistryEvent("NtSetValueKey", "before", body.str(), tid);
}

VOID AfterNtSetValueKey(THREADID tid, ADDRINT retValue) { LogZeroResultRegistry("NtSetValueKey", retValue, tid, "return"); }

/*
    Documentation (not Microsoft):
    https://ntdoc.m417z.com/ntdeletevaluekey
*/
VOID BeforeNtDeleteValueKey(THREADID tid, ADDRINT KeyHandle, ADDRINT ValueName) {
    std::ostringstream body;
    body << "\"args\":{"
         << "\"KeyHandle\":\"0x" << std::hex << KeyHandle << "\","
         << "\"ValueName\":\"0x" << std::hex << ValueName << "\""
         << "}";

    Logger::Instance().LogRegistryEvent("NtDeleteValueKey", "before", body.str(), tid);
}

VOID AfterNtDeleteValueKey(THREADID tid, ADDRINT retValue) { LogZeroResultRegistry("NtDeleteValueKey", retValue, tid, "return"); }

VOID InstrumentRegistryOperations(IMG img, VOID* v) {
    InstrumentRoutine(img, "RegOpenKeyExW", AFUNPTR(BeforeRegOpenKeyExW), AFUNPTR(AfterRegOpenKeyExW), 5);
    InstrumentRoutine(img, "RegOpenKeyExA", AFUNPTR(BeforeRegOpenKeyExA), AFUNPTR(AfterRegOpenKeyExA), 5);
    InstrumentRoutine(img, "RegCreateKeyExW", AFUNPTR(BeforeRegCreateKeyExW), AFUNPTR(AfterRegCreateKeyExW), 9);
    InstrumentRoutine(img, "RegCreateKeyExA", AFUNPTR(BeforeRegCreateKeyExA), AFUNPTR(AfterRegCreateKeyExA), 9);
    InstrumentRoutine(img, "RegSetValueExW", AFUNPTR(BeforeRegSetValueExW), AFUNPTR(AfterRegSetValueExW), 6);
    InstrumentRoutine(img, "RegSetValueExA", AFUNPTR(BeforeRegSetValueExA), AFUNPTR(AfterRegSetValueExA), 6);
    InstrumentRoutine(img, "RegQueryValueExW", AFUNPTR(BeforeRegQueryValueExW), AFUNPTR(AfterRegQueryValueExW), 6);
    InstrumentRoutine(img, "RegQueryValueExA", AFUNPTR(BeforeRegQueryValueExA), AFUNPTR(AfterRegQueryValueExA), 6);
    InstrumentRoutine(img, "RegDeleteKeyW", AFUNPTR(BeforeRegDeleteKeyW), AFUNPTR(AfterRegDeleteKeyW), 2);
    InstrumentRoutine(img, "RegDeleteKeyA", AFUNPTR(BeforeRegDeleteKeyA), AFUNPTR(AfterRegDeleteKeyA), 2);
    InstrumentRoutine(img, "RegDeleteValueW", AFUNPTR(BeforeRegDeleteValueW), AFUNPTR(AfterRegDeleteValueW), 2);
    InstrumentRoutine(img, "RegDeleteValueA", AFUNPTR(BeforeRegDeleteValueA), AFUNPTR(AfterRegDeleteValueA), 2);
    InstrumentRoutine(img, "RegEnumKeyExW", AFUNPTR(BeforeRegEnumKeyExW), AFUNPTR(AfterRegEnumKeyExW), 8);
    InstrumentRoutine(img, "RegEnumKeyExA", AFUNPTR(BeforeRegEnumKeyExA), AFUNPTR(AfterRegEnumKeyExA), 8);
    InstrumentRoutine(img, "RegEnumValueW", AFUNPTR(BeforeRegEnumValueW), AFUNPTR(AfterRegEnumValueW), 8);
    InstrumentRoutine(img, "RegEnumValueA", AFUNPTR(BeforeRegEnumValueA), AFUNPTR(AfterRegEnumValueA), 8);
    InstrumentRoutine(img, "RegCloseKey", AFUNPTR(BeforeRegCloseKey), AFUNPTR(AfterRegCloseKey), 1);
    InstrumentRoutine(img, "NtOpenKey", AFUNPTR(BeforeNtOpenKey), AFUNPTR(AfterNtOpenKey), 3);
    InstrumentRoutine(img, "NtCreateKey", AFUNPTR(BeforeNtCreateKey), AFUNPTR(AfterNtCreateKey), 7);
    InstrumentRoutine(img, "NtSetValueKey", AFUNPTR(BeforeNtSetValueKey), AFUNPTR(AfterNtSetValueKey), 6);
    InstrumentRoutine(img, "NtDeleteValueKey", AFUNPTR(BeforeNtDeleteValueKey), AFUNPTR(AfterNtDeleteValueKey), 2);
}

void StartRegistryOperationsModule() {
    IMG_AddInstrumentFunction(InstrumentRegistryOperations, 0);
}

void FinishRegistryOperationsModule() {
    Logger::Instance().LogMain("Registry operations module stopping -> Check RegistryOperations.jsonl for registry-specific Windows APIs");
}
