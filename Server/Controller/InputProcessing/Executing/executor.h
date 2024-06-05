#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "../../../../Model/Include/Enums/returnType.h"
#include "../../../../Model/Include/CodeMap/CodeMap.h"
#include "../../../ControlBlock/controlblock.h"

#include <tuple>

class Executor {
public:
    Executor(const std::string& inputFilePath);
    ~Executor() noexcept;

    int processScopeLine(int lineNumber);
    int processVariableLine(int lineNumber);
    int processFuncDeclarationLine(int lineNumber);
    int processFunctionDefinitionLine(int lineNumber, bool flag);
    void showFunctionResults();
    std::tuple<std::string, std::string, std::string> getFunctionDetails(const std::string& function); //--------------------------------
private:
    std::vector<std::string> stringCutComma(std::string line);
    bool correctArgs(std::string protoArgs, std::string implArgs);
    void connectProtToImpl();
    std::string inputFilePath_;

    struct infoFunctions {
        infoFunctions(const bool& defOrDec, const std::string& funcRetType, const std::string& funcName, const std::string& funcArgs, std::tuple<int, int, int> info)
        {
            this -> defOrDec = defOrDec;
            this -> funcRetType = funcRetType;
            this -> funcName = funcName;
            this -> funcArgs = funcArgs;
            this -> info = info;
        }

        bool defOrDec;
        std::string funcRetType;
        std::string funcName;
        std::string funcArgs;
        std::tuple<int, int, int> info;
    };

    std::vector<infoFunctions> functionArray;
    std::vector<infoFunctions> afterMainfuctionArray;
    std::vector<std::string> types;
};

#endif // EXECUTOR_H
