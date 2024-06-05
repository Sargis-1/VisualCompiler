#ifndef SEGMENTSENUM_H
#define SEGMENTSENUM_H

//enum class to differ between RamSegments, in project Segment enum's elements will explicitly be casted to integers
enum class Segment {
    Stack, //0 th index represents Stack
    Heap, //1 st index represents Heap
    SymTab, //2 nd index represents Symbol Table
    Readonly, //3 th index represents Readonly
    Bss, //4 th index represents Bss
    Data //5 th index represents Data
};

//enum class Type {
//    Bool,
//    Char,
//    Short,
//    Int,
//    Long,
//    Float,
//    Double,
//    Size_t,
//};

#endif // SEGMENTSENUM_H
