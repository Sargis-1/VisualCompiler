#ifndef STACK_H
#define STACK_H
#include "../AbstRam/absram.h"

class Stack : public AbsRam {
public:
    Stack();
    ~Stack() noexcept;
};

#endif // STACK_H
