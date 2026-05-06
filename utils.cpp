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

void InstrumentRoutine(IMG img, const char* apiName, AFUNPTR beforeFunction, AFUNPTR afterFunction, UINT32 argCount) {
    RTN rtn = RTN_FindByName(img, apiName);
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