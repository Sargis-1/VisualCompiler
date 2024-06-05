#ifndef BSS_H
#define BSS_H
#include "../AbstRam/absram.h"

class Bss : public AbsRam {
public:
    Bss();
    ~Bss() noexcept;
};

#endif // BSS_H
