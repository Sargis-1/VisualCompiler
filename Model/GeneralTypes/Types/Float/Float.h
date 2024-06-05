#ifndef Float_H
#define Float_H
#include "../Type/Type.h"

class Float : public Type
{
public:
    void resolveValue(std::string str);
    void operator=(std::string str);
    void resolveExpression(std::string str);
    std::string containsOnlyBraces(std::string str);
    std::string containsCurlyBraces(std::string str);
    void complexInitialization(std::string str);
    explicit Float(std::string current_line);
    ~Float() = default;
public: //added by me
    void resolveChar(std::string str);
    bool isHexDigit(char c);
    void determineSign(std::string& str);
    void changeSign();
    std::string simplify(std::string str);
private:
    char sign;
    float val;
};

#endif // Float_H
