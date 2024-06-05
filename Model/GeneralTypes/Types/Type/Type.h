#ifndef TYPE_H
#define TYPE_H

#include "../../BaseType/BaseType.h"

// #include "../../../../Server/Ram/RamController/RamController.h"
// #include "../../../Include/Enums/segmentsenum.h"
// #include "../../../Scope/scope.h"
// #include "../../../Include/AST/AST.h"
// #include "../../../../Observer/Provider.h"
#include "../../../Include/Operations/Operations.h"


class Type : public BaseType, public Operations {
// protected:
//     static std::map<std::string, std::string(Type::*)(std::string)> castTable;
public:
    using BaseType::SC;
//     static std::string plusOne(std::string num); //function to add 1 to any type of number
//     static std::string char_cast_to_int(std::string str);
//     static std::string intCast(std::string num);
//     static std::string charCast(std::string num);
//     static std::string floatCast(std::string num);
//     static std::string doubleCast(std::string num);
//     static std::string boolCast(std::string num);
//     static std::string shortCast(std::string num);


//     //any type must implement all the pure virtual methods of BaseType
//     //non-virtual methods are interchangeable for all the types, but may be overdefined if needed

//     Type(); //default ctor
//     std::string callToAst(std::string expr);
//     static std::string resolveOperation(std::string str);
//     std::string operator =(std::string str);
//     std::string operator +=(std::string expr);
//     std::string operator -=(std::string expr);
//     std::string operator *=(std::string expr);
//     std::string operator /=(std::string expr);
//     std::string operator %=(std::string expr);
//     std::string operator |=(std::string expr);
//     std::string operator &=(std::string expr);
//     std::string operator ^=(std::string expr);
//     std::string operator <<=(std::string expr);
//     std::string operator >>=(std::string expr);

//     static std::string logicalNot(std::string expr);
//     static std::string bitwiseNot(std::string expr); //doesnt work correctly
//     static std::string prefixIncrement(std::string expr);
//     static std::string prefixDecrement(std::string expr);
//     static std::string postfixIncrement(std::string expr);
//     static std::string postfixDecrement(std::string expr);

    virtual void resolveValue(std::string str) = 0; //for resolving contents of value
    virtual void operator=(std::string str) = 0; //main assigning logic
    virtual void resolveExpression(std::string str) = 0; //for understanding the expresion type and cordinating it to needed function
    virtual std::string containsOnlyBraces(std::string str) = 0; //brace handling
    virtual std::string containsCurlyBraces(std::string str) = 0; //curly brace handling
    virtual void complexInitialization(std::string str) = 0; //complex initialization handling // remember
    virtual ~Type();  //dtor
};

#endif // TYPE_H
