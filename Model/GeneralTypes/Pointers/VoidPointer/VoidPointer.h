#ifndef VOIDPOINTER_H
#define VOIDPOINTER_H
#include "../Pointer/Pointer.h"


class VoidPointer : public Pointer {
public:
    void resolveValue(std::string unresolved_val);
    void operator=(std::string val);
    void resolveExpression(std::string str);
    std::string containsOnlyBraces(std::string unresolved_val);
    std::string containsCurlyBraces(std::string unresolved_val);
    void complexInitialization(std::string unresolved_val);
    explicit VoidPointer(std::string current_line);
    ~VoidPointer();

};


#endif // VOIDPOINTER_H
