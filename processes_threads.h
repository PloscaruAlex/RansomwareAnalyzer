#pragma once

#include "pin.H"
#include "logger.h"
#include <sstream>
#include <string>
#include "utils.h"

std::string JoinArgv(INT argc, const CHAR* const* argv);
BOOL OnFollowChild(CHILD_PROCESS childProcess, VOID* v);
VOID OnThreadStart(THREADID tid, CONTEXT* ctxt, INT32 flags, VOID* v);

void StartProcessesThreadsModule();
void FinishProcessesThreadsModule();
