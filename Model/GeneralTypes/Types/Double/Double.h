#ifndef DOUBLE_H
#define DOUBLE_H
#include "../Type/Type.h"
#include <iostream>

class Double : public Type {
public:
    void operator =(std::string val);
    void operator +=(std::string val);
    void operator -=(std::string val);
    void operator *=(std::string val);
    void operator /=(std::string val);

    void resolveValue(std::string str);
    void resolveExpression(std::string str);
    std::string containsOnlyBraces(std::string unresolved_val);
    std::string containsCurlyBraces(std::string str);
    void complexInitialization(std::string str);
    explicit Double(std::string current_line);
    ~Double();

private:
    bool containsMinus(std::string& expression); // modifies expression and returns the mark
    void containsAllBraces(std::string& str); // called contains function
    std::string toAST(std::string expression); //work with AST
    bool isFunction(std::string str);
    std::string eraseBracesOfFunction(std::string str, int token_number);

private:
    bool isCalledAlready;
};

#endif // DOUBLE_H
