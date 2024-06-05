#include "stack.h"

Stack::Stack() : AbsRam(Segment::Stack, 0x00000000, 0x00000000) //Initializing Starting and current addresses of this Segment
{

}

Stack::~Stack() noexcept
{

}

