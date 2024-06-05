#ifndef CONDITIONALS_H
#define CONDITIONALS_H
#include "../../../../Server/ControlBlock/controlblock.h"

class Conditionals {
public:
    Conditionals();

    //operator int to cast this object to newLineNumber
    operator int();//to return line number after if/else block to run

protected:
     int returnedValue;
     ControlBlock* CB;
     //struct to hold if/else blocks start end lineNumbers and which is of them true
     struct Block {
         bool condition = false;
         int startNumber = 0;
         int endNumber = 0;
     } block;

     bool conditionHandler(std::string code);
     void assignFlag(bool& flag, std::string code);
     virtual void initializeBlock(int lineNumber) = 0;
     virtual void execute() = 0;
};

#endif // CONDITIONALS_H
