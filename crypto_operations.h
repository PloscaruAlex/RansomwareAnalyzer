#pragma once

#include "pin.H"
#include "logger.h"
#include <sstream>
#include <string>
#include "utils.h"

void LogHandleResultCrypto(const std::string& api, ADDRINT retValue, THREADID tid, const char* fieldName);

VOID BeforeCryptDeriveKey(THREADID tid, ADDRINT hProv, ADDRINT Algid, ADDRINT hBaseData, ADDRINT dwFlags, ADDRINT phKey);
VOID AfterCryptDeriveKey(THREADID tid, ADDRINT retValue);

VOID BeforeCryptDecodeObject(THREADID tid, ADDRINT dwCertEncodingType, ADDRINT lpszStructType, ADDRINT pbEncoded, ADDRINT cbEncoded, ADDRINT dwFlags, ADDRINT pvStructInfo, ADDRINT pcbStructInfo);
VOID AfterCryptDecodeObject(THREADID tid, ADDRINT retValue);

VOID BeforeCryptDecodeObjectEx(THREADID tid, ADDRINT dwCertEncodingType, ADDRINT lpszStructType, ADDRINT pbEncoded, ADDRINT cbEncoded, ADDRINT dwFlags, ADDRINT pDecodePara, ADDRINT pvStructInfo, ADDRINT pcbStructInfo);
VOID AfterCryptDecodeObjectEx(THREADID tid, ADDRINT retValue);

VOID BeforeCryptGenKey(THREADID tid, ADDRINT hProv, ADDRINT Algid, ADDRINT dwFlags, ADDRINT phKey);
VOID AfterCryptGenKey(THREADID tid, ADDRINT retValue);

VOID BeforeCryptImportPublicKeyInfo(THREADID tid, ADDRINT hCryptProv, ADDRINT dwCertEncodingType, ADDRINT pInfo, ADDRINT phKey);
VOID AfterCryptImportPublicKeyInfo(THREADID tid, ADDRINT retValue);

VOID BeforeCryptAcquireContextW(THREADID tid, ADDRINT phProv, ADDRINT pszContainer, ADDRINT pszProvider, ADDRINT dwProvType, ADDRINT dwFlags);
VOID AfterCryptAcquireContextW(THREADID tid, ADDRINT retValue);

VOID BeforeCryptAcquireContextA(THREADID tid, ADDRINT phProv, ADDRINT pszContainer, ADDRINT pszProvider, ADDRINT dwProvType, ADDRINT dwFlags);
VOID AfterCryptAcquireContextA(THREADID tid, ADDRINT retValue);

VOID BeforeCryptCreateHash(THREADID tid, ADDRINT hProv, ADDRINT Algid, ADDRINT hKey, ADDRINT dwFlags, ADDRINT phHash);
VOID AfterCryptCreateHash(THREADID tid, ADDRINT retValue);

VOID BeforeCryptHashData(THREADID tid, ADDRINT hHash, ADDRINT pbData, ADDRINT dwDataLen, ADDRINT dwFlags);
VOID AfterCryptHashData(THREADID tid, ADDRINT retValue);

VOID BeforeCryptEncrypt(THREADID tid, ADDRINT hKey, ADDRINT hHash, ADDRINT Final, ADDRINT dwFlags, ADDRINT pbData, ADDRINT pdwDataLen, ADDRINT dwBufLen);
VOID AfterCryptEncrypt(THREADID tid, ADDRINT retValue);

VOID BeforeCryptDecrypt(THREADID tid, ADDRINT hKey, ADDRINT hHash, ADDRINT Final, ADDRINT dwFlags, ADDRINT pbData, ADDRINT pdwDataLen);
VOID AfterCryptDecrypt(THREADID tid, ADDRINT retValue);

VOID BeforeCryptImportKey(THREADID tid, ADDRINT hProv, ADDRINT pbData, ADDRINT dwDataLen, ADDRINT hPubKey, ADDRINT dwFlags, ADDRINT phKey);
VOID AfterCryptImportKey(THREADID tid, ADDRINT retValue);

VOID BeforeCryptExportKey(THREADID tid, ADDRINT hKey, ADDRINT hExpKey, ADDRINT dwBlobType, ADDRINT dwFlags, ADDRINT pbData, ADDRINT pdwDataLen);
VOID AfterCryptExportKey(THREADID tid, ADDRINT retValue);

VOID BeforeCryptDestroyKey(THREADID tid, ADDRINT hKey);
VOID AfterCryptDestroyKey(THREADID tid, ADDRINT retValue);

VOID InstrumentCryptoOperations(IMG img, VOID* v);

void StartCryptoOperationsModule();
void FinishCryptoOperationsModule();
