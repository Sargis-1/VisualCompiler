#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "../../Include/AST/AST.h"
#include "../../Scope/scope.h"

class Operations {
protected:
    std::map<std::string, std::string(Operations::*)(std::string)> castTable;
public:

    Operations();
    Operations(std::string expression);

    std::string plusOne(std::string num); //function to add 1 to any type of number
    std::string char_cast_to_int(std::string str); //function to cast character to an int value
    //functions to cast numbers to appropriate tyes, all of them return casted values
    std::string intCast(std::string num);
    std::string charCast(std::string num);
    std::string floatCast(std::string num);
    std::string doubleCast(std::string num);
    std::string boolCast(std::string num);
    std::string shortCast(std::string num);

    std::string logicalNot(std::string expr); //function to logically negate the received value
    std::string bitwiseNot(std::string expr); //function to negate all the bits of a recieved value doesnt work correctly
    std::string prefixIncrement(std::string expr); //function to increment variable's value by one and return changed value of a variable
    std::string prefixDecrement(std::string expr);
    std::string postfixIncrement(std::string expr); //function to increment variable's value by one and return initaial value of a variable
    std::string postfixDecrement(std::string expr);

    std::string resolveOperation(std::string str); //function to resolve which operation is used in recieved expression
    std::string callToAst(std::string expr);
//  std::string operator =(std::string str);
    std::string operator +=(std::string expr);
    std::string operator -=(std::string expr);
    std::string operator *=(std::string expr);
    std::string operator /=(std::string expr);
    std::string operator %=(std::string expr);
    std::string operator |=(std::string expr);
    std::string operator &=(std::string expr);
    std::string operator ^=(std::string expr);
    std::string operator <<=(std::string expr);
    std::string operator >>=(std::string expr);

    std::pair<std::string, std::string> getResultAndVariable_type(); //must return  <result, var_type/var_name>
    std::vector<std::string>  tokenizing(std::string str);
    Scope* SC;

private:
    std::string expression;
    std::string var_type;
    std::string result;
};

#endif // OPERATIONS_H
