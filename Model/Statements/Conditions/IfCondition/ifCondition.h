#ifndef IFCONDITION_H
#define IFCONDITION_H

#include "../Conditionals/Conditionals.h"

class ifCondition : public Conditionals {
public:
     ifCondition(std::string ifStatement, int lineNumber);
    ~ifCondition() = default;

     //helpers
     void calculateBlockEnd(std::stack<char>& curlyBrackets, int lineNumber);
     bool elseOrElseIf(std::string code);
     void initializeBlock(int lineNumber) override;
     void execute() override;
};

#endif // IFCONDITION_H
