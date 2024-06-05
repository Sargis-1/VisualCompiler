#ifndef BOOL_H
#define BOOL_H
#include "../Type/Type.h"


class Bool : public Type {

public:
    Bool(std::string current_line);
    std::string containsOnlyBraces(std::string unresolved_val);
    std::string containsCurlyBraces(std::string unresolved_val);
    std::string resolvingRightHandOperand(std::string);
    void resolveExpression(std::string);
    void resolveValue(std::string str);
    void operator=(std::string str);
    void tokenizeByComma(std::string expr);
    void complexInitialization(std::string str);
    ~Bool();
    bool isFunction(std::string);
private:
    std::string expression;
};

#endif //BOOL_H
