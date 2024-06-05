#include "heap.h"

Heap::Heap() : AbsRam(Segment::Heap, 0x59999995, 0x59999995)//Initializing Starting and current addresses of this Segment
{

}

Heap::~Heap() noexcept
{

}
