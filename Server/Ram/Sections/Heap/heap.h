#ifndef HEAP_H
#define HEAP_H
#include "../AbstRam/absram.h"

class Heap : public AbsRam {
public:
    Heap();
    ~Heap() noexcept;
};

#endif // HEAP_H
