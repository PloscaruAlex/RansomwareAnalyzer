#include "logger.h"

#include <ctime>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <iostream>

KNOB<std::string> KnobMainOutputFile(
    KNOB_MODE_WRITEONCE,
    "pintool",
    "o-main",
    "RansomwareAnalyzer.log",
    "specify file name for main log output"
);

KNOB<std::string> KnobDLLOutputFile(
    KNOB_MODE_WRITEONCE,
    "pintool",
    "o-dll",
    "DLLmodule.jsonl",
    "specify file name for DLL module"
);

KNOB<std::string> KnobAPIOutputFile(
    KNOB_MODE_WRITEONCE,
    "pintool",
    "o-api",
    "APImodule.jsonl",
    "specify file name for API module"
);

KNOB<std::string> KnobFileOpsOutputFile(
    KNOB_MODE_WRITEONCE,
    "pintool",
    "o-file",
    "FileOperations.jsonl",
    "specify file name for file operations module"
);

KNOB<std::string> KnobRegistryOpsOutputFile(
    KNOB_MODE_WRITEONCE,
    "pintool",
    "o-reg",
    "RegistryOperations.jsonl",
    "specify file name for registry operations module"
);

KNOB<std::string> KnobCryptoOpsOutputFile(
    KNOB_MODE_WRITEONCE,
    "pintool",
    "o-crypto",
    "CryptoOperations.jsonl",
    "specify file name for crypto module"
);

KNOB<std::string> KnobThreadOutputFile(
    KNOB_MODE_WRITEONCE,
    "pintool",
    "o-thread",
    "ProcessThread.jsonl",
    "specify file name for process/thread module"
);

Logger& Logger::Instance() {
    static Logger instance;
    return instance;
}

Logger::Logger() : initialized_(false) {}

Logger::~Logger() {
    Shutdown();
}

VOID Logger::Init() {
    if (initialized_)
        return;

    InitSink(mainLog_, KnobMainOutputFile.Value(), 10);
    InitSink(dllLog_, KnobDLLOutputFile.Value(), 10);
    InitSink(apiLog_, KnobAPIOutputFile.Value(), 10000);
    InitSink(fileLog_, KnobFileOpsOutputFile.Value(), 1000);
    InitSink(regLog_, KnobRegistryOpsOutputFile.Value(), 1000);
    InitSink(cryptoLog_, KnobCryptoOpsOutputFile.Value(), 1000);
    InitSink(threadLog_, KnobThreadOutputFile.Value(), 10);
    

    initialized_ = true;
    LogMain("Logger module initialized");
}

VOID Logger::Shutdown() {
    if (!initialized_)
        return;

    LogMain("Logger module shutting down");

    CloseSink(mainLog_);
    CloseSink(dllLog_);
    CloseSink(apiLog_);
    CloseSink(fileLog_);
    CloseSink(regLog_);
    CloseSink(cryptoLog_);
    CloseSink(threadLog_);
    
    initialized_ = false;
}

long long Logger::MakeTimestampMs() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()
    ).count();
}

std::string Logger::MakeTimestamp() {
    const auto now = std::chrono::system_clock::now();
    const auto now_time_t = std::chrono::system_clock::to_time_t(now);
    const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

    std::tm tmValue;
#ifdef __CYGWIN32__
    localtime_s(&tmValue, &now_time_t);
#else
    localtime_r(&now_time_t, &tmValue);
#endif

    std::ostringstream oss;
    oss << std::put_time(&tmValue, "%Y-%m-%d %H:%M:%S")
        << '.'
        << std::setfill('0') << std::setw(3) << ms.count();

    return oss.str();
}

std::string Logger::JsonEscape(const std::string& input) {
    std::ostringstream oss;
    for (size_t i = 0; i < input.size(); ++i) {
        unsigned char c = static_cast<unsigned char>(input[i]);
        switch (c) {
        case '"': 
            oss << "\\\""; 
            break;
        case '\\': 
            oss << "\\\\"; 
            break;
        case '\b': 
            oss << "\\b"; 
            break;
        case '\f': 
            oss << "\\f"; 
            break;
        case '\n': 
            oss << "\\n"; 
            break;
        case '\r': 
            oss << "\\r"; 
            break;
        case '\t': 
            oss << "\\t"; 
            break;
        default:
            if (c < 0x20) {
                oss << "\\u00" << std::hex << std::uppercase << ((c >> 4) & 0xF) << (c & 0xF) << std::nouppercase << std::dec;
            }
            else {
                oss << input[i];
            }
            break;
        }
    }
    return oss.str();
}

UINT32 Logger::CurrentPid() {
    return static_cast<UINT32>(PIN_GetPid());
}

std::string Logger::MakePerProcessFileName(const std::string& baseFileName, UINT32 pid) {
    std::ostringstream oss;

    std::string::size_type dotPos = baseFileName.find_last_of('.');
    if (dotPos == std::string::npos || dotPos == 0) {
        oss << baseFileName << "." << std::dec << pid;
    } else {
        oss << baseFileName.substr(0, dotPos)
            << "."
            << std::dec << pid
            << baseFileName.substr(dotPos);
    }

    return oss.str();
}

VOID Logger::LogMain(const std::string& line, THREADID tid) {
    WriteLine(mainLog_, line, tid);
}

VOID Logger::LogDllLoad(const std::string& imageName, UINT32 imageId, ADDRINT base, ADDRINT high, THREADID tid) {
    std::ostringstream oss;
    oss << "{"
        //<< "\"timestamp\":\"" << Logger::JsonEscape(Logger::MakeTimestamp()) << "\","
        << "\"timestamp_ms\":" << Logger::MakeTimestampMs() << ","
        << "\"process_id\":" << Logger::CurrentPid() << ",";

    if (tid != INVALID_THREADID) {
        oss << "\"thread_id\":" << std::dec << tid << ",";
    }

    oss << "\"image_name\":\"" << Logger::JsonEscape(imageName) << "\","
        << "\"image_id\":" << std::dec << imageId << ","
        << "\"base\":\"0x" << std::hex << base << "\","
        << "\"high\":\"0x" << std::hex << high << "\""
        << "}";

    WriteJsonLine(dllLog_, oss.str(), tid);
}


VOID Logger::LogApiCall(const std::string& dllName, const std::string& funcName, ADDRINT instructionPointer, THREADID tid) {
    std::ostringstream oss;
    oss << "{"
        //<< "\"timestamp\":\"" << Logger::JsonEscape(Logger::MakeTimestamp()) << "\","
        << "\"timestamp_ms\":" << Logger::MakeTimestampMs() << ","
        << "\"process_id\":" << Logger::CurrentPid() << ",";

    if (tid != INVALID_THREADID) {
        oss << "\"thread_id\":" << std::dec << tid << ",";
    }

    oss << "\"instruction_pointer\":\"0x" << std::hex << instructionPointer << "\","
        << "\"dllName\":\"" << Logger::JsonEscape(dllName) << "\","
        << "\"apiName\":\"" << Logger::JsonEscape(funcName) << "\""
        << "}";

    WriteJsonLine(apiLog_, oss.str(), tid);
}

VOID Logger::LogFileEvent(const std::string& api, const std::string& stage, const std::string& args, THREADID tid) {
    std::ostringstream oss;
    oss << "{"
        //<< "\"timestamp\":\"" << Logger::JsonEscape(Logger::MakeTimestamp()) << "\","
        << "\"timestamp_ms\":" << Logger::MakeTimestampMs() << ","
        << "\"api\":\"" << Logger::JsonEscape(api) << "\","
        << "\"stage\":\"" << Logger::JsonEscape(stage) << "\","
        << "\"process_id\":" << Logger::CurrentPid();

    if (tid != INVALID_THREADID) {
        oss << ",\"thread_id\":" << std::dec << tid;
    }

    if (!args.empty()) {
        oss << "," << args;
    }

    oss << "}";
    WriteJsonLine(fileLog_, oss.str(), tid);
}


VOID Logger::LogRegistryEvent(const std::string& api, const std::string& stage, const std::string& args, THREADID tid) {
    std::ostringstream oss;
    oss << "{"
        // << "\"timestamp\":\"" << Logger::JsonEscape(Logger::MakeTimestamp()) << "\","
        << "\"timestamp_ms\":" << Logger::MakeTimestampMs() << ","
        << "\"api\":\"" << Logger::JsonEscape(api) << "\","
        << "\"stage\":\"" << Logger::JsonEscape(stage) << "\","
        << "\"process_id\":" << Logger::CurrentPid();

    if (tid != INVALID_THREADID) {
        oss << ",\"thread_id\":" << std::dec << tid;
    }

    if (!args.empty()) {
        oss << "," << args;
    }

    oss << "}";
    WriteJsonLine(regLog_, oss.str(), tid);
}

VOID Logger::LogCryptoEvent(const std::string& api, const std::string& stage, const std::string& args, THREADID tid) {
    std::ostringstream oss;
    oss << "{"
        // << "\"timestamp\":\"" << Logger::JsonEscape(Logger::MakeTimestamp()) << "\","
        << "\"timestamp_ms\":" << Logger::MakeTimestampMs() << ","
        << "\"api\":\"" << Logger::JsonEscape(api) << "\","
        << "\"stage\":\"" << Logger::JsonEscape(stage) << "\","
        << "\"process_id\":" << Logger::CurrentPid();

    if (tid != INVALID_THREADID) {
        oss << ",\"thread_id\":" << std::dec << tid;
    }

    if (!args.empty()) {
        oss << "," << args;
    }

    oss << "}";
    WriteJsonLine(cryptoLog_, oss.str(), tid);
}

VOID Logger::LogProcess(const std::string& line, THREADID tid) {
    WriteJsonLine(threadLog_, line, tid);
}

UINT32 Logger::LockValue(THREADID tid) {
    return (tid == INVALID_THREADID) ? 1 : (static_cast<UINT32>(tid) + 1);
}

VOID Logger::InitSink(LogSink& sink, const std::string& fileName, int flushEveryN) {
    const UINT32 pid = CurrentPid();
    sink.fileName = MakePerProcessFileName(fileName, pid);
    PIN_InitLock(&sink.lock);
    sink.stream.open(sink.fileName.c_str(), std::ios::out | std::ios::trunc);
    sink.linesWritten = 0;

    sink.initialized = sink.stream.is_open();

    sink.flushEveryN = flushEveryN;

    if (!sink.initialized) {
        std::cerr << "Failed to open log file: " << fileName << std::endl;
    }
}

VOID Logger::CloseSink(LogSink& sink) {
    if (!sink.initialized)
        return;

    PIN_GetLock(&sink.lock, 1);
    if (sink.stream.is_open()) {
        sink.stream.flush();
        sink.stream.close();
    }
    sink.initialized = false;
    PIN_ReleaseLock(&sink.lock);
}

VOID Logger::WriteLine(LogSink& sink, const std::string& line, THREADID tid) {
    if (!sink.initialized)
        return;

    PIN_GetLock(&sink.lock, LockValue(tid));

    if (sink.stream.is_open()) {
        sink.stream << "[" << Logger::MakeTimestamp() << "]";
        sink.stream << "[pid=" << std::dec << Logger::CurrentPid() << "]";

        if (tid != INVALID_THREADID) {
            sink.stream << "[tid=" << std::dec << tid << "]";
        }

        sink.stream << " " << line << std::endl;
        sink.linesWritten++;

        if ((sink.linesWritten % sink.flushEveryN) == 0) {
            sink.stream.flush();
        }
    }

    PIN_ReleaseLock(&sink.lock);
}


/*
    std::endl flushes every time it is used, so it defeats the purpose of interval flusing:
    https://stackoverflow.com/questions/4751972/endl-and-flushing-the-buffer
*/
VOID Logger::WriteJsonLine(LogSink& sink, const std::string& json, THREADID tid) {
    if (!sink.initialized)
        return;

    PIN_GetLock(&sink.lock, LockValue(tid));

    if (sink.stream.is_open()) {
        sink.stream << json << '\n';
        
        sink.linesWritten++;
        if ((sink.linesWritten % sink.flushEveryN) == 0) {
            sink.stream.flush();
        }
    }

    PIN_ReleaseLock(&sink.lock);
}
