#ifndef Short_H
#define Short_H
#include "../Type/Type.h"
#include "../../../Include/AST/AST.h"
#include "../../../Scope/scope.h"


class Short : public Type {
public:
    explicit Short(std::string current_line);
    ~Short();
    void resolveExpression(std::string str);
    void resolveValue(std::string str);
    void operator =(std::string str);
    std::string operator +=(std::string str);
    std::string operator -=(std::string str);
    std::string operator *=(std::string str);
    std::string operator /=(std::string str);
    std::string operator %=(std::string str);
    std::string operator |=(std::string str);
    std::string operator &=(std::string str);
    std::string operator ^=(std::string str);
    std::string operator <<=(std::string str);
    std::string operator >>=(std::string str);
    std::string resolveApostrophe(std::string str);
    std::string containsOnlyBraces(std::string str);
    std::string containsCurlyBraces(std::string str);
    void complexInitialization(std::string str);
private:
    bool sign = false;
    void change_sign(std::string& str);
    std::string checkSize(std::string str);
    std::string resolveAST(std::string str);
    bool isFunction(std::string str);
    void reserveOperators(std::string name, std::string tok);
    int countNonDefaultCtorFunctions(std::string str);
};

#endif // Short_H
