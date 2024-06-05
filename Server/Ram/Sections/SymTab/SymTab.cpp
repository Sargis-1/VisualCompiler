#include "SymTab.h"

SymTab::SymTab() : AbsRam(Segment::SymTab, 0, 0) //SymTab segment has no addresses, because it contains only function names
{

}

SymTab::~SymTab() noexcept
{

}

std::string SymTab::generateAddress(int size)
{
    return "";
}
