#include "readonly.h"

ReadOnly::ReadOnly() : AbsRam(Segment::Readonly, 0xB333332B, 0xB333332B) //Initializing Starting and current addresses of this Segment
{

}

ReadOnly::~ReadOnly() noexcept
{

}
