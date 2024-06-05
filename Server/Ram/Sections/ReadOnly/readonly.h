#ifndef READONLY_H
#define READONLY_H
#include "../AbstRam/absram.h"

class ReadOnly : public AbsRam {
public:
    ReadOnly();
    ~ReadOnly() noexcept;
};

#endif // READONLY_H
