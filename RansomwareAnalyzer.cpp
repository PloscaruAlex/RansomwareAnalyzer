#include "pin.H"
#include <iostream>
#include <fstream>
#include <ctime>

#include "logger.h"
#include "utils.h"
#include "dll_module.h"
//#include "api_module.h"
#include "file_operations.h"
#include "registry_operations.h"
#include "processes_threads.h"
#include "crypto_operations.h"

INT32 Usage() {
    std::cerr << "This Pintool gathers the following information from a ransomware sample at runtime: " << std::endl;
    std::cerr << "  - DLLs: loading sequence and full path;" << std::endl;
    // std::cerr << "  - API sequence: the order in which Windows APIs and syscalls are called;" << std::endl;
    std::cerr << "  - File operations: file-oriented Windows APIs calls + arguments;" << std::endl;
    std::cerr << "  - Registry operations: registry-oriented Windows APIs calls + arguments;" << std::endl;
    std::cerr << "  - Crypto operations: crypto Windows APIs calls + arguments;" << std::endl;
    std::cerr << "  - Processes and threads: what child processes are created by the sample and how many threads it uses;" << std::endl;
    std::cerr << std::endl;
    std::cerr << "To run the pintool, use the following command: " << std::endl;
    std::cerr << "<PIN> -t <ARANCINO> -t <PATH_TO_PINTOOL> -- <RANSOMWARE_SAMPLE>" << std::endl;

    std::cerr << std::endl << KNOB_BASE::StringKnobSummary() << std::endl;
    return -1;
}

void StartAllModules() {
    Logger::Instance().Init();
    Logger::Instance().LogMain("Ransomware Analyzer pintool started");

    Logger::Instance().LogMain("Starting DLL module ...");
    StartDLLModule();

    // Logger::Instance().LogMain("Starting API module ...");
    // StartAPIModule();

    Logger::Instance().LogMain("Starting File Operations module ...");
    StartFileOperationsModule();

    Logger::Instance().LogMain("Starting Registry Operations module ...");
    StartRegistryOperationsModule();

    Logger::Instance().LogMain("Starting Crypto Operations module ...");
    StartCryptoOperationsModule();

    Logger::Instance().LogMain("Starting Processes and Threads module ...");
    StartProcessesThreadsModule();

    Logger::Instance().LogMain("All modules started.");
}

VOID Fini(INT32 code, VOID* v) {
    FinishDLLModule();
    // FinishAPIModule();
    FinishFileOperationsModule();
    FinishRegistryOperationsModule();
    FinishCryptoOperationsModule();
    FinishProcessesThreadsModule();

    Logger::Instance().LogMain("Ransomware Analyzer pintool stopping");
    Logger::Instance().Shutdown();
}

int main(int argc, char* argv[]) {

    PIN_InitSymbols();

    if (PIN_Init(argc, argv)) return Usage();

    StartAllModules();
    PIN_AddFiniFunction(Fini, 0);

    PIN_StartProgram();

    return 0;
}
