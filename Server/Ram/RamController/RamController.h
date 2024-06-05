#ifndef RAMCONTROLLER_H
#define RAMCONTROLLER_H
#include "../Sections/AbstRam/absram.h"
#include "../Sections/Stack/stack.h"
#include "../Sections/Heap/heap.h"
#include "../Sections/SymTab/SymTab.h"
#include "../Sections/ReadOnly/readonly.h"
#include "../Sections/Bss/bss.h"
#include "../Sections/Data/data.h"

//Struct to gather all Ram Segment pointers in one object and later use that object to change all segments
struct RamController {
    AbsRam* stack;
    AbsRam* heap;
    AbsRam* symtab;
    AbsRam* readonly;
    AbsRam* bss;
    AbsRam* data;
    static RamController* getRamController(); //Method to get this class object

private:
    RamController(); //Private ctor to enforce Singleton pattern
    static RamController* instance; //Pointer to instance of this class object
};

#endif // RAMCONTROLLER_H
