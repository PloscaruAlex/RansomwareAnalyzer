#ifndef LOGGER_H
#define LOGGER_H

#include "pin.H"
#include <fstream>
#include <string>

class Logger {
public:
    static Logger& Instance();

    VOID Init();
    VOID Shutdown();

    static std::string JsonEscape(const std::string& input);
    static long long MakeTimestampMs();
    static std::string MakeTimestamp();
    static UINT32 CurrentPid();
    static std::string MakePerProcessFileName(const std::string& baseFileName, UINT32 pid);

    VOID LogMain(const std::string& line, THREADID tid = INVALID_THREADID);
    VOID LogDllLoad(const std::string& imageName, UINT32 imageId, ADDRINT base, ADDRINT high, THREADID tid = INVALID_THREADID);
    VOID LogApiCall(const std::string& dllName, const std::string& funcName, ADDRINT instructionPointer, THREADID tid = INVALID_THREADID);
    VOID LogFileEvent(const std::string& api, const std::string& stage, const std::string& args, THREADID tid = INVALID_THREADID);
    VOID LogRegistryEvent(const std::string& api, const std::string& stage, const std::string& args, THREADID tid = INVALID_THREADID);
    VOID LogCryptoEvent(const std::string& api, const std::string& stage, const std::string& args, THREADID tid = INVALID_THREADID);
    VOID LogProcess(const std::string& line, THREADID tid = INVALID_THREADID);
private:
    Logger();
    ~Logger();
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    struct LogSink {
        std::ofstream stream;
        PIN_LOCK lock;
        std::string fileName;
        bool initialized;
        LogSink() : initialized(false) {}
    };

    LogSink mainLog_;
    LogSink dllLog_;
    LogSink apiLog_;
    LogSink fileLog_;
    LogSink regLog_;
    LogSink threadLog_;
    LogSink cryptoLog_;
    bool initialized_;

    static UINT32 LockValue(THREADID tid);
    VOID InitSink(LogSink& sink, const std::string& fileName);
    VOID CloseSink(LogSink& sink);
    VOID WriteLine(LogSink& sink, const std::string& line, THREADID tid);
    VOID WriteJsonLine(LogSink& sink, const std::string& json, THREADID tid);
};

extern KNOB<std::string> KnobMainOutputFile;
extern KNOB<std::string> KnobDLLOutputFile;
extern KNOB<std::string> KnobAPIOutputFile;
extern KNOB<std::string> KnobFileOpsOutputFile;
extern KNOB<std::string> KnobRegistryOpsOutputFile;
extern KNOB<std::string> KnobCryptoOpsOutputFile;
extern KNOB<std::string> KnobThreadOutputFile;

#endif
