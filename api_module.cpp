#include "api_module.h"

static VOID WindowsAPICall(THREADID tid, ADDRINT instructionPointer, ADDRINT dllNamePtr, ADDRINT funcNamePtr, ADDRINT funcAddr) {
    const char* dllName = reinterpret_cast<const char*>(dllNamePtr);
    const char* funcName = reinterpret_cast<const char*>(funcNamePtr);

    Logger::Instance().LogApiCall(
        dllName,
        funcName,
        instructionPointer,
        tid
    );
}

static VOID InstrumentAllAPICalls(IMG img, VOID* v) {
    for (SEC sec = IMG_SecHead(img); SEC_Valid(sec); sec = SEC_Next(sec)) {
        for (RTN rtn = SEC_RtnHead(sec); RTN_Valid(rtn); rtn = RTN_Next(rtn)) {
            std::string* imgName = new std::string(IMG_Name(img));
            std::string* rtnName = new std::string(RTN_Name(rtn));
            
            ADDRINT rtnAddr = RTN_Address(rtn);
            RTN_Open(rtn);
            RTN_InsertCall(
                rtn,
                IPOINT_BEFORE,
                AFUNPTR(WindowsAPICall),
                IARG_THREAD_ID,
                IARG_INST_PTR,
                IARG_ADDRINT, reinterpret_cast<ADDRINT>(imgName->c_str()),
                IARG_ADDRINT, reinterpret_cast<ADDRINT>(rtnName->c_str()),
                IARG_ADDRINT, rtnAddr,
                IARG_END
            );
            RTN_Close(rtn);
        }
    }
}

void StartAPIModule() {
    IMG_AddInstrumentFunction(InstrumentAllAPICalls, 0);
}

void FinishAPIModule() {
    Logger::Instance().LogMain("API module stopping -> Check APImodule.jsonl for all Windows API calls");
}
