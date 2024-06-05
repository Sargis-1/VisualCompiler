#include "Conditionals.h"

#include "../../../Include/AST/AST.h"

Conditionals::Conditionals()
    :
      returnedValue(0),
      CB(ControlBlock::getControlBlock())
{
}

bool Conditionals::conditionHandler(std::string code)
{
    // if (any condition) {
    // } else if (any condtion) {
    //while (any condition) {
    int startIndex = 0;
    int endIndex = code.size() - 1;
    while (code[startIndex] != '(') {
        ++startIndex;
    }
    ++startIndex;


    while (code[endIndex] != ')') {
        --endIndex;
    }

    code = code.substr(startIndex, endIndex - startIndex); //code = any condition

    if (code.find("true") != std::string::npos) { //if condition is true or false
        return true;
    } else if (code.find("false") != std::string::npos) {
        return false;
    }

    //int x = 10; or x = 20;
    std::vector<std::string> tokens;
    std::string token;
    std::stringstream ss(code);
    while (ss >> token) {
        tokens.push_back(token);
    }

    auto it = std::find(tokens.begin(), tokens.end(), "=");
    if (it != tokens.end()) {
        CB -> processString(startIndex, code + ";", false);
        //get value from UI
        Scope* scope = Scope::getScope();
        return std::stoi(scope -> getValueByName(*(--it)).first);
    }

    //std::cout << __func__  << "code: " << code << std::endl;
    return AST(code);
}

void Conditionals::assignFlag(bool &flag, std::string code)
{
    std::string token;
    std::istringstream iss(code);
    iss >> token; // token is "}"
    if (iss >> token) {// token is "else"
        flag = true;
    } else {//if/else block end code line
        flag = false;
    }
}

Conditionals::operator int()
{
    return this -> returnedValue;//endNumber is last executing line in last block
}
