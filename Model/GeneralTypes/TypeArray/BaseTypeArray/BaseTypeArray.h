#ifndef BASETYPEARRAY_H
#define BASETYPEARRAY_H

#include "../../BaseType/BaseType.h"

#include "../../../Include/Enums/segmentsenum.h"
#include "../../../Scope/scope.h"
#include "../../../Include/Operations/Operations.h"


class BaseTypeArray : public BaseType
{
public:
    virtual void operator =(std::string unresolved_val) = 0;
    virtual void resolveExpression(std::string str) = 0;
    void ShowInUI(int ArrSize);
    void ShowInUI(int ArrSize, std::vector<std::string> vec);

    virtual ~BaseTypeArray();
};

#endif // BASETYPEARRAY_H
