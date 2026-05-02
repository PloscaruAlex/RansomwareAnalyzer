#include "crypto_operations.h"

void LogHandleResultCrypto(const std::string& api, ADDRINT retValue, THREADID tid, const char* fieldName) {
    std::ostringstream body;
    body << "\"result\":{"
         << "\"" << fieldName << "\":\"0x" << std::hex << retValue << "\","
         << "\"success\":" << ((retValue != 0 && retValue != static_cast<ADDRINT>(-1)) ? "true" : "false")
         << "}";
    Logger::Instance().LogCryptoEvent(api, "after", body.str(), tid);
}

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/wincrypt/nf-wincrypt-cryptderivekey
*/
VOID BeforeCryptDeriveKey(THREADID tid, ADDRINT hProv, ADDRINT Algid, ADDRINT hBaseData, ADDRINT dwFlags, ADDRINT phKey) {
    std::ostringstream body;
    body << "\"args\":{"
         << "\"hProv\":\"0x" << std::hex << hProv << "\","
         << "\"Algid\":\"0x" << std::hex << Algid << "\","
         << "\"hBaseData\":\"0x" << std::hex << hBaseData << "\","
         << "\"dwFlags\":\"0x" << std::hex << dwFlags << "\","
         << "\"phKey\":\"0x" << std::hex << phKey << "\""
         << "}";

    Logger::Instance().LogCryptoEvent("CryptDeriveKey", "before", body.str(), tid);
}

VOID AfterCryptDeriveKey(THREADID tid, ADDRINT retValue) { LogHandleResultCrypto("CryptDeriveKey", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/wincrypt/nf-wincrypt-cryptdecodeobject
*/
VOID BeforeCryptDecodeObject(THREADID tid, ADDRINT dwCertEncodingType, ADDRINT lpszStructType, ADDRINT pbEncoded, ADDRINT cbEncoded, ADDRINT dwFlags, ADDRINT pvStructInfo, ADDRINT pcbStructInfo) {
    std::ostringstream body;
    body << "\"args\":{"
         << "\"dwCertEncodingType\":\"0x" << std::hex << dwCertEncodingType << "\","
         << "\"lpszStructType\":\"0x" << std::hex << lpszStructType << "\","
         << "\"pbEncoded\":\"0x" << std::hex << pbEncoded << "\","
         << "\"cbEncoded\":\"0x" << std::hex << cbEncoded << "\","
         << "\"dwFlags\":\"0x" << std::hex << dwFlags << "\","
         << "\"pvStructInfo\":\"0x" << std::hex << pvStructInfo << "\","
         << "\"pcbStructInfo\":\"0x" << std::hex << pcbStructInfo << "\""
         << "}";

    Logger::Instance().LogCryptoEvent("CryptDecodeObject", "before", body.str(), tid);
}

VOID AfterCryptDecodeObject(THREADID tid, ADDRINT retValue) { LogHandleResultCrypto("CryptDecodeObject", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/wincrypt/nf-wincrypt-cryptdecodeobjectex
*/
VOID BeforeCryptDecodeObjectEx(THREADID tid, ADDRINT dwCertEncodingType, ADDRINT lpszStructType, ADDRINT pbEncoded, ADDRINT cbEncoded, ADDRINT dwFlags, ADDRINT pDecodePara, ADDRINT pvStructInfo, ADDRINT pcbStructInfo) {
    std::ostringstream body;
    body << "\"args\":{"
         << "\"dwCertEncodingType\":\"0x" << std::hex << dwCertEncodingType << "\","
         << "\"lpszStructType\":\"0x" << std::hex << lpszStructType << "\","
         << "\"pbEncoded\":\"0x" << std::hex << pbEncoded << "\","
         << "\"cbEncoded\":\"0x" << std::hex << cbEncoded << "\","
         << "\"dwFlags\":\"0x" << std::hex << dwFlags << "\","
         << "\"pDecodePara\":\"0x" << std::hex << pDecodePara << "\","
         << "\"pvStructInfo\":\"0x" << std::hex << pvStructInfo << "\","
         << "\"pcbStructInfo\":\"0x" << std::hex << pcbStructInfo << "\""
         << "}";

    Logger::Instance().LogCryptoEvent("CryptDecodeObjectEx", "before", body.str(), tid);
}

VOID AfterCryptDecodeObjectEx(THREADID tid, ADDRINT retValue) { LogHandleResultCrypto("CryptDecodeObjectEx", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/wincrypt/nf-wincrypt-cryptgenkey
*/
VOID BeforeCryptGenKey(THREADID tid, ADDRINT hProv, ADDRINT Algid, ADDRINT dwFlags, ADDRINT phKey) {
    std::ostringstream body;
    body << "\"args\":{"
         << "\"hProv\":\"0x" << std::hex << hProv << "\","
         << "\"Algid\":\"0x" << std::hex << Algid << "\","
         << "\"dwFlags\":\"0x" << std::hex << dwFlags << "\","
         << "\"phKey\":\"0x" << std::hex << phKey << "\""
         << "}";

    Logger::Instance().LogCryptoEvent("CryptGenKey", "before", body.str(), tid);
}

VOID AfterCryptGenKey(THREADID tid, ADDRINT retValue) { LogHandleResultCrypto("CryptGenKey", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/wincrypt/nf-wincrypt-cryptimportpublickeyinfo
*/
VOID BeforeCryptImportPublicKeyInfo(THREADID tid, ADDRINT hCryptProv, ADDRINT dwCertEncodingType, ADDRINT pInfo, ADDRINT phKey) {
    std::ostringstream body;
    body << "\"args\":{"
         << "\"hCryptProv\":\"0x" << std::hex << hCryptProv << "\","
         << "\"dwCertEncodingType\":\"0x" << std::hex << dwCertEncodingType << "\","
         << "\"pInfo\":\"0x" << std::hex << pInfo << "\","
         << "\"phKey\":\"0x" << std::hex << phKey << "\""
         << "}";

    Logger::Instance().LogCryptoEvent("CryptImportPublicKeyInfo", "before", body.str(), tid);
}

VOID AfterCryptImportPublicKeyInfo(THREADID tid, ADDRINT retValue) { LogHandleResultCrypto("CryptImportPublicKeyInfo", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/wincrypt/nf-wincrypt-cryptacquirecontextw
*/
VOID BeforeCryptAcquireContextW(THREADID tid, ADDRINT phProv, ADDRINT pszContainer, ADDRINT pszProvider, ADDRINT dwProvType, ADDRINT dwFlags) {
    std::wstring container = ReadWideString(reinterpret_cast<const wchar_t*>(pszContainer));
    std::wstring provider = ReadWideString(reinterpret_cast<const wchar_t*>(pszProvider));

    std::ostringstream body;
    body << "\"args\":{"
         << "\"phProv\":\"0x" << std::hex << phProv << "\","
         << "\"pszContainer\":\"" << Logger::JsonEscape(convertWideToStr(container)) << "\","
         << "\"pszProvider\":\"" << Logger::JsonEscape(convertWideToStr(provider)) << "\","
         << "\"dwProvType\":\"0x" << std::hex << dwProvType << "\","
         << "\"dwFlags\":\"0x" << std::hex << dwFlags << "\""
         << "}";

    Logger::Instance().LogCryptoEvent("CryptAcquireContextW", "before", body.str(), tid);
}

VOID AfterCryptAcquireContextW(THREADID tid, ADDRINT retValue) { LogHandleResultCrypto("CryptAcquireContextW", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/wincrypt/nf-wincrypt-cryptacquirecontexta
*/
VOID BeforeCryptAcquireContextA(THREADID tid, ADDRINT phProv, ADDRINT pszContainer, ADDRINT pszProvider, ADDRINT dwProvType, ADDRINT dwFlags) {
    std::string container = ReadAnsiString(reinterpret_cast<const char*>(pszContainer));
    std::string provider = ReadAnsiString(reinterpret_cast<const char*>(pszProvider));

    std::ostringstream body;
    body << "\"args\":{"
         << "\"phProv\":\"0x" << std::hex << phProv << "\","
         << "\"pszContainer\":\"" << Logger::JsonEscape(container) << "\","
         << "\"pszProvider\":\"" << Logger::JsonEscape(provider) << "\","
         << "\"dwProvType\":\"0x" << std::hex << dwProvType << "\","
         << "\"dwFlags\":\"0x" << std::hex << dwFlags << "\""
         << "}";

    Logger::Instance().LogCryptoEvent("CryptAcquireContextA", "before", body.str(), tid);
}

VOID AfterCryptAcquireContextA(THREADID tid, ADDRINT retValue) { LogHandleResultCrypto("CryptAcquireContextA", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/wincrypt/nf-wincrypt-cryptcreatehash
*/
VOID BeforeCryptCreateHash(THREADID tid, ADDRINT hProv, ADDRINT Algid, ADDRINT hKey, ADDRINT dwFlags, ADDRINT phHash) {
    std::ostringstream body;
    body << "\"args\":{"
         << "\"hProv\":\"0x" << std::hex << hProv << "\","
         << "\"Algid\":\"0x" << std::hex << Algid << "\","
         << "\"hKey\":\"0x" << std::hex << hKey << "\","
         << "\"dwFlags\":\"0x" << std::hex << dwFlags << "\","
         << "\"phHash\":\"0x" << std::hex << phHash << "\""
         << "}";

    Logger::Instance().LogCryptoEvent("CryptCreateHash", "before", body.str(), tid);
}

VOID AfterCryptCreateHash(THREADID tid, ADDRINT retValue) { LogHandleResultCrypto("CryptCreateHash", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/wincrypt/nf-wincrypt-crypthashdata
*/
VOID BeforeCryptHashData(THREADID tid, ADDRINT hHash, ADDRINT pbData, ADDRINT dwDataLen, ADDRINT dwFlags) {
    std::ostringstream body;
    body << "\"args\":{"
         << "\"hHash\":\"0x" << std::hex << hHash << "\","
         << "\"pbData\":\"0x" << std::hex << pbData << "\","
         << "\"dwDataLen\":\"0x" << std::hex << dwDataLen << "\","
         << "\"dwFlags\":\"0x" << std::hex << dwFlags << "\""
         << "}";

    Logger::Instance().LogCryptoEvent("CryptHashData", "before", body.str(), tid);
}

VOID AfterCryptHashData(THREADID tid, ADDRINT retValue) { LogHandleResultCrypto("CryptHashData", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/wincrypt/nf-wincrypt-cryptencrypt
*/
VOID BeforeCryptEncrypt(THREADID tid, ADDRINT hKey, ADDRINT hHash, ADDRINT Final, ADDRINT dwFlags, ADDRINT pbData, ADDRINT pdwDataLen, ADDRINT dwBufLen) {
    std::ostringstream body;
    body << "\"args\":{"
         << "\"hKey\":\"0x" << std::hex << hKey << "\","
         << "\"hHash\":\"0x" << std::hex << hHash << "\","
         << "\"Final\":\"0x" << std::hex << Final << "\","
         << "\"dwFlags\":\"0x" << std::hex << dwFlags << "\","
         << "\"pbData\":\"0x" << std::hex << pbData << "\","
         << "\"pdwDataLen\":\"0x" << std::hex << pdwDataLen << "\","
         << "\"dwBufLen\":\"0x" << std::hex << dwBufLen << "\""
         << "}";

    Logger::Instance().LogCryptoEvent("CryptEncrypt", "before", body.str(), tid);
}

VOID AfterCryptEncrypt(THREADID tid, ADDRINT retValue) { LogHandleResultCrypto("CryptEncrypt", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/wincrypt/nf-wincrypt-cryptdecrypt
*/
VOID BeforeCryptDecrypt(THREADID tid, ADDRINT hKey, ADDRINT hHash, ADDRINT Final, ADDRINT dwFlags, ADDRINT pbData, ADDRINT pdwDataLen) {
    std::ostringstream body;
    body << "\"args\":{"
         << "\"hKey\":\"0x" << std::hex << hKey << "\","
         << "\"hHash\":\"0x" << std::hex << hHash << "\","
         << "\"Final\":\"0x" << std::hex << Final << "\","
         << "\"dwFlags\":\"0x" << std::hex << dwFlags << "\","
         << "\"pbData\":\"0x" << std::hex << pbData << "\","
         << "\"pdwDataLen\":\"0x" << std::hex << pdwDataLen << "\""
         << "}";

    Logger::Instance().LogCryptoEvent("CryptDecrypt", "before", body.str(), tid);
}

VOID AfterCryptDecrypt(THREADID tid, ADDRINT retValue) { LogHandleResultCrypto("CryptDecrypt", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/wincrypt/nf-wincrypt-cryptimportkey
*/
VOID BeforeCryptImportKey(THREADID tid, ADDRINT hProv, ADDRINT pbData, ADDRINT dwDataLen, ADDRINT hPubKey, ADDRINT dwFlags, ADDRINT phKey) {
    std::ostringstream body;
    body << "\"args\":{"
         << "\"hProv\":\"0x" << std::hex << hProv << "\","
         << "\"pbData\":\"0x" << std::hex << pbData << "\","
         << "\"dwDataLen\":\"0x" << std::hex << dwDataLen << "\","
         << "\"hPubKey\":\"0x" << std::hex << hPubKey << "\","
         << "\"dwFlags\":\"0x" << std::hex << dwFlags << "\","
         << "\"phKey\":\"0x" << std::hex << phKey << "\""
         << "}";

    Logger::Instance().LogCryptoEvent("CryptImportKey", "before", body.str(), tid);
}

VOID AfterCryptImportKey(THREADID tid, ADDRINT retValue) { LogHandleResultCrypto("CryptImportKey", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/wincrypt/nf-wincrypt-cryptexportkey
*/
VOID BeforeCryptExportKey(THREADID tid, ADDRINT hKey, ADDRINT hExpKey, ADDRINT dwBlobType, ADDRINT dwFlags, ADDRINT pbData, ADDRINT pdwDataLen) {
    std::ostringstream body;
    body << "\"args\":{"
         << "\"hKey\":\"0x" << std::hex << hKey << "\","
         << "\"hExpKey\":\"0x" << std::hex << hExpKey << "\","
         << "\"dwBlobType\":\"0x" << std::hex << dwBlobType << "\","
         << "\"dwFlags\":\"0x" << std::hex << dwFlags << "\","
         << "\"pbData\":\"0x" << std::hex << pbData << "\","
         << "\"pdwDataLen\":\"0x" << std::hex << pdwDataLen << "\""
         << "}";

    Logger::Instance().LogCryptoEvent("CryptExportKey", "before", body.str(), tid);
}

VOID AfterCryptExportKey(THREADID tid, ADDRINT retValue) { LogHandleResultCrypto("CryptExportKey", retValue, tid, "return"); }

/*
    Microsoft Documentation:
    https://learn.microsoft.com/en-us/windows/win32/api/wincrypt/nf-wincrypt-cryptdestroykey
*/
VOID BeforeCryptDestroyKey(THREADID tid, ADDRINT hKey) {
    std::ostringstream body;
    body << "\"args\":{"
         << "\"hKey\":\"0x" << std::hex << hKey << "\""
         << "}";

    Logger::Instance().LogCryptoEvent("CryptDestroyKey", "before", body.str(), tid);
}

VOID AfterCryptDestroyKey(THREADID tid, ADDRINT retValue) { LogHandleResultCrypto("CryptDestroyKey", retValue, tid, "return"); }


VOID InstrumentCryptoOperations(IMG img, VOID* v) {
    InstrumentRoutine(img, "CryptDeriveKey", AFUNPTR(BeforeCryptDeriveKey), AFUNPTR(AfterCryptDeriveKey), 5);
    InstrumentRoutine(img, "CryptDecodeObject", AFUNPTR(BeforeCryptDecodeObject), AFUNPTR(AfterCryptDecodeObject), 7);
    InstrumentRoutine(img, "CryptDecodeObjectEx", AFUNPTR(BeforeCryptDecodeObjectEx), AFUNPTR(AfterCryptDecodeObjectEx), 8);
    InstrumentRoutine(img, "CryptGenKey", AFUNPTR(BeforeCryptGenKey), AFUNPTR(AfterCryptGenKey), 4);
    InstrumentRoutine(img, "CryptImportPublicKeyInfo", AFUNPTR(BeforeCryptImportPublicKeyInfo), AFUNPTR(AfterCryptImportPublicKeyInfo), 4);
    InstrumentRoutine(img, "CryptAcquireContextW", AFUNPTR(BeforeCryptAcquireContextW), AFUNPTR(AfterCryptAcquireContextW), 5);
    InstrumentRoutine(img, "CryptAcquireContextA", AFUNPTR(BeforeCryptAcquireContextA), AFUNPTR(AfterCryptAcquireContextA), 5);
    InstrumentRoutine(img, "CryptCreateHash", AFUNPTR(BeforeCryptCreateHash), AFUNPTR(AfterCryptCreateHash), 5);
    InstrumentRoutine(img, "CryptHashData", AFUNPTR(BeforeCryptHashData), AFUNPTR(AfterCryptHashData), 4);
    InstrumentRoutine(img, "CryptEncrypt", AFUNPTR(BeforeCryptEncrypt), AFUNPTR(AfterCryptEncrypt), 7);
    InstrumentRoutine(img, "CryptDecrypt", AFUNPTR(BeforeCryptDecrypt), AFUNPTR(AfterCryptDecrypt), 6);
    InstrumentRoutine(img, "CryptImportKey", AFUNPTR(BeforeCryptImportKey), AFUNPTR(AfterCryptImportKey), 6);
    InstrumentRoutine(img, "CryptExportKey", AFUNPTR(BeforeCryptExportKey), AFUNPTR(AfterCryptExportKey), 6);
    InstrumentRoutine(img, "CryptDestroyKey", AFUNPTR(BeforeCryptDestroyKey), AFUNPTR(AfterCryptDestroyKey), 1);
}

void StartCryptoOperationsModule() {
    IMG_AddInstrumentFunction(InstrumentCryptoOperations, 0);
}

void FinishCryptoOperationsModule() {
    Logger::Instance().LogMain("Crypto operations module stopping -> Check CryptoOperations.jsonl for crypto-specific Windows APIs");
}
