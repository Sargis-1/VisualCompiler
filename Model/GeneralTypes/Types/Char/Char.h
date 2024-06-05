#ifndef CHAR_H
#define CHAR_H
#include "../Type/Type.h"
//#include "../../../Include/AST/AST.h"

class Char : public Type {
public:
    explicit Char(std::string current_line);
    ~Char();
    void resolveExpression(std::string str);
    void resolveValue(std::string str);
    void operator= (std::string str);
    std::string operator+= (std::string str);
    std::string operator-= (std::string str);
    std::string operator*= (std::string str);
    std::string operator/= (std::string str);
    std::string operator%= (std::string str);
    std::string operator|= (std::string str);
    std::string operator&= (std::string str);
    std::string operator^= (std::string str);
    std::string operator<<= (std::string str);
    std::string operator>>= (std::string str);
    std::string containsOnlyBraces(std::string str);
    std::string containsCurlyBraces(std::string str);
    std::string check_size(std::string str);
    std::string resolve_ast(std::string str);
    std::string get_value(std::string str);
    void complexInitialization(std::string str);

private:
    bool sign = false;
    void sign_helper(std::string& str);
};

#endif // CHAR_H
