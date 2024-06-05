#ifndef WHILE_H
#define WHILE_H
#include "../Conditionals/Conditionals.h"

class While : public Conditionals {
public:
    While(std::string ifStatement, int lineNumber);

    bool isRepeatable();//while codition is true, function will return true
    void takeBreak();
    void execute() override;//executes while cycle

private:
    void initializeBlock(int lineNumber) override;//initializes condition, start and end of while block
};

#endif // WHILE_H
