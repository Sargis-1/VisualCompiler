#ifndef SHORTARRAY_H
#define SHORTARRAY_H

#include "../BaseTypeArray/BaseTypeArray.h"

class ShortArray : public BaseTypeArray
{
public:
    explicit ShortArray(std::string current_line);
    void resolveExpression(std::string str);
    void operator =(std::string str);
    std::vector<std::string> resolveValue(std::string str);
    std::string resolveAST(std::string str);
    int resolveSize(std::string str);
    void foo(std::string str);
    void Show(int size);

     ~ShortArray();
private:
    bool flag;


};
#endif // SHORTARRAY_H
