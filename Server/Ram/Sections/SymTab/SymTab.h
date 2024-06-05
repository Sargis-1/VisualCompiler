#ifndef SymTab_H
#define SymTab_H
#include "../AbstRam/absram.h"

class SymTab : public AbsRam {
public:
    SymTab();
    ~SymTab() noexcept;
    std::string generateAddress(int size) override; //SymTab segment overrides this method,
    //because it doesnt have addresses like other SymTabs
};

#endif // SymTab_H
