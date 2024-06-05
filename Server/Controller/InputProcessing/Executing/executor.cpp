#include "executor.h"

#include "../../../../Model/Include/CodeMap/CodeMap.h"
#include "../Utilities/functionparser.h"
#include "../../../Ram/Sections/SymTab/SymTab.h"

#include <string>
#include <regex>

Executor::Executor(const std::string &inputFilePath) : inputFilePath_(inputFilePath)
{
    types = {"int", "double", "float", "char", "bool", "short", "void", "const", "static", "unsigned", "signed"};
}

Executor::~Executor() noexcept
{

}

int Executor::processScopeLine(int startLineNumber)
{
    std::stack<char> scope;
    std::string lineChecking = codeMap -> getCode(startLineNumber);
    //std::cout << lineChecking << std::endl;
    if (lineChecking[0] == '{') {
        scope.push('{');
    } else {
        throw std::runtime_error("Something is wrong in processScopeLine");
    }

    while (!scope.empty()) {
        lineChecking = codeMap -> getCode(++startLineNumber);
        for (int i = 0; i < lineChecking.size(); ++i) {
            if (lineChecking[i] == '{') {
                scope.push('{');
            } else if (lineChecking[i] == '}') {
                scope.pop();
            }
        }
    }
    return startLineNumber; // '}'
}

int Executor::processVariableLine(int lineNumber)
{
    return ++lineNumber;
}

int Executor::processFuncDeclarationLine(int lineNumber)
{
    std::string function = codeMap -> getCode(lineNumber);
    std::string funcRetType = FunctionParser::extractReturnType(function);
    std::string funcArgs = FunctionParser::extractArguments(function);
    if (funcArgs == "") {
       funcArgs = "No Arguments";
    }
    std::string funcName = FunctionParser::extractFunctionName(function);
    functionArray.emplace_back(true, funcRetType, funcName, funcArgs, std::make_tuple(lineNumber, -1, -1));
//    SymTab section;
//    section.pushFunctionSlot(funcRetType, funcName, funcArgs, std::make_tuple(lineNumber, -1, -1));
    return ++lineNumber;
}

int Executor::processFunctionDefinitionLine(int lineNumber, bool flag)
{
    std::string function = codeMap -> getCode(lineNumber);
    function += ";";
    std::string funcRetType = FunctionParser::extractReturnType(function);
    std::string funcArgs = FunctionParser::extractArguments(function);
    if (funcArgs == "") {
       funcArgs = "No Arguments";
    }
    std::string funcName = FunctionParser::extractFunctionName(function);
    int endLine = processScopeLine(lineNumber + 1);
    //auto info = std::make_tuple(-1, lineNumber, endLine);
    if (flag) {
        functionArray.emplace_back(false, funcRetType, funcName, funcArgs, std::make_tuple(-1, lineNumber, endLine));
    } else {
        afterMainfuctionArray.emplace_back(true, funcRetType, funcName, funcArgs, std::make_tuple(-1, lineNumber, endLine));
    }
//    SymTab section;
//    section.pushFunctionSlot(funcRetType, funcName, funcArgs, info);
    return ++endLine;
}


std::vector<std::string> Executor::stringCutComma(std::string line)
{
    std::stringstream ss(line);
    std::string token;
    std::vector<std::string> tokens;
    while (std::getline(ss, token, ',')) {
        tokens.push_back(token);
    }

    return tokens;
}

bool Executor::correctArgs(std::string protoArgs, std::string implArgs)
{
    std::vector<std::string> correctTypes;
    std::vector<std::string> tokens = stringCutComma(protoArgs);
    std::vector<std::string> tokens1 = stringCutComma(implArgs);
    if (tokens.size() != tokens1.size()) {
        return false;
    }
    for (auto token : tokens) {
        std::stringstream ss(token);
        std::string tmp;
        bool flag;
        while (ss >> tmp) {
            flag = true;
            for (const auto& str : types) {
               if (tmp.find(str) != std::string::npos) { // -----------------------------  referenc and pointers
                   correctTypes.push_back(tmp);
                   flag = false;
               }
            }
            if (flag) {
                break;
            }
        }
    }

    int i = 0;
    for (auto token : tokens1) {
        std::stringstream ss(token);
        std::string tmp;
        bool flag;
        while (ss >> tmp) {
            flag = true;
            for (const auto& str : types) {
               if (tmp.find(str) != std::string::npos) {
                   if (i >= correctTypes.size()) {
                       return false;
                   }

                   if (correctTypes[i] != tmp) {
                       return false;
                   }
                   ++i;
                   flag = false;
               }
            }
            if (flag) {
                break;
            }
        }
    }
    return true;
}

void Executor::connectProtToImpl()
{
    for (auto& it : functionArray) {
        if (it.defOrDec) {
            for (auto& findName : afterMainfuctionArray) {
                if (findName.defOrDec && findName.funcName == it.funcName && findName.funcRetType == it.funcRetType) {
                    if (correctArgs(findName.funcArgs, it.funcArgs)) {
                        findName.defOrDec = false;
                        it.defOrDec = false;
                        std::get<1>(it.info) = std::get<1>(findName.info);
                        std::get<2>(it.info) = std::get<2>(findName.info);
                    }
                }
            }
        }
    }
}

void Executor::showFunctionResults()
{
    std::vector<std::pair<int, int>> preMain;
    for (auto it : functionArray) {
        if (it.defOrDec) {
            preMain.push_back(std::make_pair(std::get<0>(it.info), std::get<0>(it.info)));
        } else {
            preMain.push_back(std::make_pair(std::get<1>(it.info), std::get<2>(it.info)));
        }
    }
    ControlBlock* cb = ControlBlock::getControlBlock();
    cb -> setPreMain(preMain);
    connectProtToImpl();
    SymTab section;
    for (auto it : functionArray) {
        //std::cout << it.funcName << " " << std::get<0>(it.info) << " " << std::get<1>(it.info) << " " << std::get<2>(it.info) << std::endl;
        section.pushFunctionSlot(it.funcRetType, it.funcName, it.funcArgs, it.info);
    }
    QTimer* timer = new QTimer();
    QEventLoop* loop = new QEventLoop();
    QObject::connect(timer, &QTimer::timeout, loop, &QEventLoop::quit);
    timer -> setInterval(1000);
    timer -> start();
    loop -> exec();
}

std::tuple<std::string, std::string, std::string> Executor::getFunctionDetails(const std::string &function)
{
    return {"", "", ""};
}
