#pragma once

#include "pin.H"
#include <sstream>
#include <string>
#include <locale>
#include <codecvt>

#define UNKNOWN_ADDR ~ADDRINT(0)

std::wstring ReadWideString(const wchar_t* appPtr, size_t maxChars = 1024);
std::string ReadAnsiString(const char* appPtr, size_t maxChars = 512);
std::string convertWideToStr(const std::wstring& ws);
void InstrumentRoutine(IMG img, const char* apiName, AFUNPTR beforeFunction, AFUNPTR afterFunction, UINT32 argCount);
