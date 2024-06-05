#ifndef DOUBLEARRAY_H
#define DOUBLEARRAY_H

#include "../BaseTypeArray/BaseTypeArray.h"

class DoubleArray : public BaseTypeArray
{
public:
    DoubleArray(std::string codeLine);
    void resolveExpression(std::string unresolved_val);
    void operator =(std::string unresolved_val);

    virtual ~DoubleArray();
};

#endif // DOUBLEARRAY_H
