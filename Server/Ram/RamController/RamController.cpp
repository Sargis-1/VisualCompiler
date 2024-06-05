#include "RamController.h"


RamController* RamController::instance = nullptr;

RamController::RamController() :
    stack(new Stack()), heap(new Heap()), symtab(new SymTab()),//initializing all pointers
    readonly(new ReadOnly()), bss(new Bss()), data(new Data())
{
}

RamController* RamController::getRamController()
{
    if (!instance) {//If no RamController was created until current time, create one and return, if was created only return it
        instance = new RamController;
    }
    return instance;
}
