#ifndef INT_H
#define INT_H
#include "../Type/Type.h"
#include "../../../Include/AST/AST.h"
class Int : public Type {
public:
    Int(std::string current_line);
    // ~Int() = default;
    ~Int();
    std::string containsOnlyBraces(std::string unresolved_val);
    std::string containsCurlyBraces(std::string unresolved_val);
    std::string resolvingRightHandOperand(std::string);
    void resolveExpression(std::string);
    void resolveValue(std::string str);
    void operator=(std::string str);
    void tokenizeByComma(std::string expr);
    void complexInitialization(std::string str);
    bool isFunction(std::string expression);
    // std::string operator +=(std::string str);
    // std::string operator -=(std::string str);
    // std::string operator *=(std::string str);
    // std::string operator /=(std::string str);
    // std::string operator %=(std::string str);
    // std::string operator |=(std::string str);
    // std::string operator &=(std::string str);
    // std::string operator ^=(std::string str);
    // std::string operator <<=(std::string str);
    // std::string operator >>=(std::string str);
private:
    std::string expression;
};
#endif // INT_H
