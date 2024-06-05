#include "While.h"

While::While(std::string ifStatement, int lineNumber)
    :
      Conditionals()
{
    this -> initializeBlock(lineNumber);
}

bool While::isRepeatable()
{
    this -> block.condition = conditionHandler(codeMap -> getCode(block.startNumber - 1));
    return block.condition;
}

void While::takeBreak()
{
    returnedValue = block.endNumber + 1;
}

void While::initializeBlock(int lineNumber)
{
    this -> block.startNumber = lineNumber + 1;//set first executing line number

    std::stack<char> curlyBrackets;//to get block end line number
    curlyBrackets.push('{'); //first curly bracket, iteration will start from if/else block first line
    bool flag = true;//to indicate the end point of while

    while (flag) {
        ++lineNumber;//increment lineNumber to get next executing code line
        std::string code = codeMap -> getCode(lineNumber);
        for (int i = 0; code[i] != '\0'; ++i) {
            if (code[i] == '{') {
                curlyBrackets.push(code[i]);
            } else if (code[i] == '}') {
                curlyBrackets.pop();
                if (curlyBrackets.empty()) {
                    break;
                }
            }
        }

        if (curlyBrackets.empty()) {//if stack is empty, it indicates the end of the block
            block.endNumber = lineNumber - 1;
            returnedValue = block.endNumber + 1;
            flag = false;
            //if flag false, while iteration breaks
        }
    }
}

void While::execute()
{
    for (int start = block.startNumber; start <= block.endNumber; ++start) {
        std::string currentCodeLine = codeMap -> getCode(start);
        std::string firstToken;
        std::istringstream iss(currentCodeLine);
        iss >> firstToken;

        if (firstToken == "return") {//if in while block there is function return statment
            this -> returnedValue = start;
            break;
        } else if (firstToken == "continue;" || firstToken == "break;") {
            returnedValue = start;
            break;
        }
        if (start == this -> block.startNumber) {
            QEventLoop loop;
            QTimer timer;
            QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
            timer.setInterval(1500);
            timer.start();
            loop.exec();
        }
        CB -> processString(start);

        currentCodeLine = codeMap -> getCode(start);
        std::istringstream iss1(currentCodeLine);
        iss1 >> firstToken;

        if (firstToken == "return") {
            this -> returnedValue = start;
            break;
        }
    }
}
