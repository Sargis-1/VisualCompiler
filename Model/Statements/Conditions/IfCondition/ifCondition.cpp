#include "./ifCondition.h"
#include "../../../Scope/scope.h"


ifCondition::ifCondition(std::string ifStatement, int lineNumber)
    :
      Conditionals()
{
    this -> initializeBlock(lineNumber);
    this -> execute();
}

void ifCondition::initializeBlock(int lineNumber)
{
    this -> block.condition = conditionHandler(codeMap -> getCode(lineNumber));
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

        if (curlyBrackets.empty()) {//if stack is empty, it indicates the end of block
            this -> block.endNumber = lineNumber - 1;
            if (this -> block.condition) {
                flag = false;
            } else {
                this -> assignFlag(flag, code);//if code's line is } will return false, otherwise true
            }

            if (flag) {
                //assign block condition
                if (elseOrElseIf(code)) {// } else if (condition) {
                    this -> block.condition = conditionHandler(code);
                } else {// } else {
                    this -> block.condition = true;
                }
                this -> block.startNumber = lineNumber + 1;
                curlyBrackets.push('{'); //first curly bracket, iteration will start from if/else block first line
            } else {//if the true block is found, needs to count the end of the entire if/else block
                calculateBlockEnd(curlyBrackets, lineNumber);
            }
            //if flag false, while iteration breaks
        }
    }
}

void ifCondition::calculateBlockEnd(std::stack<char>& curlyBrackets, int lineNumber)
{
    bool flag;
    assignFlag(flag, codeMap -> getCode(lineNumber));

    curlyBrackets.push('{');//} else if (any condition) {

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

        if (curlyBrackets.empty()) {
            this -> assignFlag(flag, code);
            if (flag) {
                curlyBrackets.push('{'); //first curly bracket, iteration will start from if/else block first line
            }
            //if flag false, while iteration breaks
        }
    }
    returnedValue = lineNumber;
}

bool ifCondition::elseOrElseIf(std::string code)
{
    std::string token;
    std::istringstream iss(code);
    iss >> token;// token is "}"
    if (iss >> token) {
        if (token == "else") {
            if (iss >> token) {
                if (token == "if") {
                    return true;//if code is } else if () {
                }
                return false;
            }
        }
    }
    return false;//if code is } else {
}

void ifCondition::execute()
{
    int start = this -> block.startNumber;
    int end = this -> block.endNumber;

    if (this -> block.condition) {
        for (; start <= end; ++start) {
            std::string currentCodeLine = codeMap -> getCode(start);
            std::string firstToken;
            std::istringstream iss(currentCodeLine);
            iss >> firstToken;
            if (firstToken == "return" || firstToken == "break;" || firstToken == "continue;") {//if in if/else blocks there is function return statment
                this -> returnedValue = start;
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

            if (firstToken == "return" || firstToken == "break;" || firstToken == "continue;") {
                this -> returnedValue = start;
                break;
            }
        }
    }
}
