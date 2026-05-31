#include "utils.h"

std::wstring ReadWideString(const wchar_t* appPtr, size_t maxChars) {
    std::wstring result;
    if (!appPtr)
        return result;

    for (size_t i = 0; i < maxChars; ++i) {
        wchar_t ch = 0;
        size_t copied = PIN_SafeCopy(&ch, reinterpret_cast<const VOID*>(appPtr + i), sizeof(wchar_t));
        if (copied != sizeof(wchar_t))
            break;
        if (ch == L'\0')
            break;
        result.push_back(ch);
    }
    return result;
}

std::string ReadAnsiString(const char* appPtr, size_t maxChars) {
    std::string result;
    if (!appPtr) {
        return result;
    }

    for (size_t i = 0; i < maxChars; ++i) {
        char ch = 0;
        size_t copied = PIN_SafeCopy(&ch, reinterpret_cast<const VOID*>(appPtr + i), sizeof(char));
        if (copied != sizeof(char) || ch == '\0') {
            break;
        }
        result.push_back(ch);
    }
    return result;
}

/*
    Modified as found here: https://stackoverflow.com/questions/4804298/how-to-convert-wstring-into-string
    To remove the conversion to '?' in paths and file names
*/
std::string convertWideToStr(const std::wstring& ws) {
    // std::string s;
    // s.reserve(ws.size());
    // for (wchar_t ch : ws) {
    //     if (ch >= 0 && ch <= 0x7F) {
    //         s.push_back(static_cast<char>(ch));
    //     } else {
    //         s.push_back('?');
    //     }
    // }
    // return s;

    using convert_type = std::codecvt_utf8<wchar_t>;
    std::wstring_convert<convert_type, wchar_t> converter;
    return converter.to_bytes(ws);
}


static bool AddressIsExecutable(IMG img, ADDRINT addr) {
    for (SEC sec = IMG_SecHead(img); SEC_Valid(sec); sec = SEC_Next(sec)) {
        if (!SEC_IsExecutable(sec))
            continue;
        ADDRINT secStart = SEC_Address(sec);
        ADDRINT secEnd   = secStart + SEC_Size(sec);
        if (addr >= secStart && addr < secEnd)
            return true;
    }
    return false;
}

/*
    Added from tiny tracer t oresolve the stubs and tail calling that was crashing the network operations module
    https://github.com/hasherezade/tiny_tracer/blob/b9d0a7e6c8a38cbbb12f6e66f8034a61d845d885/ModuleInfo.cpp#L100
*/
static RTN FindRoutineBySymbol(IMG img, const char* apiName) {
    for (SYM sym = IMG_RegsymHead(img); SYM_Valid(sym); sym = SYM_Next(sym)) {
        const std::string undName =
            PIN_UndecorateSymbolName(SYM_Name(sym), UNDECORATION_NAME_ONLY);
        if (undName != apiName)
            continue;
 
        const ADDRINT offset = SYM_Value(sym);
        if (offset == UNKNOWN_ADDR)
            continue;
 
        const ADDRINT addr = IMG_LowAddress(img) + offset;
 
        // Skip forwarded exports: their RVA points into the .edata section,
        // not into executable code.  Calling RTN_FindByAddress there gives a
        // broken RTN that silently swallows IPOINT_BEFORE callbacks.
        if (!AddressIsExecutable(img, addr))
            continue;
 
        RTN rtn = RTN_FindByAddress(addr);
        if (RTN_Valid(rtn))
            return rtn;
    }
 
    // Fallback for functions not found via the symbol table.
    return RTN_FindByName(img, apiName);
}

void InstrumentRoutine(IMG img, const char* apiName, AFUNPTR beforeFunction, AFUNPTR afterFunction, UINT32 argCount) {
    RTN rtn = FindRoutineBySymbol(img, apiName);
    if (!RTN_Valid(rtn)) {
        return;
    }

    RTN_Open(rtn);

    if (beforeFunction != 0) {
        switch (argCount) {
        case 1:
            RTN_InsertCall(rtn, IPOINT_BEFORE, beforeFunction,
                IARG_THREAD_ID,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
                IARG_END);
            break;
        case 2:
            RTN_InsertCall(rtn, IPOINT_BEFORE, beforeFunction,
                IARG_THREAD_ID,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 1,
                IARG_END);
            break;
        case 3:
            RTN_InsertCall(rtn, IPOINT_BEFORE, beforeFunction,
                IARG_THREAD_ID,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 1,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 2,
                IARG_END);
            break;
        case 4:
            RTN_InsertCall(rtn, IPOINT_BEFORE, beforeFunction,
                IARG_THREAD_ID,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 1,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 2,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 3,
                IARG_END);
            break;
        case 5:
            RTN_InsertCall(rtn, IPOINT_BEFORE, beforeFunction,
                IARG_THREAD_ID,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 1,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 2,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 3,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 4,
                IARG_END);
            break;
        case 6:
            RTN_InsertCall(rtn, IPOINT_BEFORE, beforeFunction,
                IARG_THREAD_ID,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 1,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 2,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 3,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 4,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 5,
                IARG_END);
            break;
        case 7:
            RTN_InsertCall(rtn, IPOINT_BEFORE, beforeFunction,
                IARG_THREAD_ID,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 1,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 2,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 3,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 4,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 5,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 6,
                IARG_END);
            break;
        case 8:
            RTN_InsertCall(rtn, IPOINT_BEFORE, beforeFunction,
                IARG_THREAD_ID,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 1,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 2,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 3,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 4,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 5,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 6,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 7,
                IARG_END);
            break;
        case 9:
            RTN_InsertCall(rtn, IPOINT_BEFORE, beforeFunction,
                IARG_THREAD_ID,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 0,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 1,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 2,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 3,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 4,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 5,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 6,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 7,
                IARG_FUNCARG_ENTRYPOINT_VALUE, 8,
                IARG_END);
            break;
        default:
            break;
        }
    }

    if (afterFunction != 0) {
        RTN_InsertCall(rtn, IPOINT_AFTER, afterFunction,
            IARG_THREAD_ID,
            IARG_FUNCRET_EXITPOINT_VALUE,
            IARG_END);
    }

    RTN_Close(rtn);
}