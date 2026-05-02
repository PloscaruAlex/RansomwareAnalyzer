#include "dll_module.h"

VOID ImageLoad(IMG img, VOID* v) {
    Logger::Instance().LogDllLoad(
        IMG_Name(img),
        IMG_Id(img),
        IMG_LowAddress(img),
        IMG_HighAddress(img)
    );
}

void StartDLLModule() {
    IMG_AddInstrumentFunction(ImageLoad, 0);
}

void FinishDLLModule() {
    Logger::Instance().LogMain("DLL module stopping -> Check DLLmodule.jsonl for DLL loading sequence");
}
