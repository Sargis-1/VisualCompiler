#ifndef FUNCTION_H
#define FUNCTION_H
#include "../../Include/AST/AST.h"
#include "../../../Server/ControlBlock/controlblock.h"
#include "../../../Server/Ram/RamController/RamController.h"

class Function
{
private:
    std::string returnType;
    std::string name;
    ControlBlock* CB;
    RamController* RC;
    Scope* SC;
    std::string call;
    int startLine = 0;
    int endLine = 0;
    std::string prototype;
    std::vector<std::pair<double, std::string>> args;
    std::vector<std::tuple<std::string, int, int, int>> info;
    int i;

public:
    Function(std::string call, std::vector<std::pair<double, std::string>>& args,std::string name = "");
    ~Function();
    void executeFunction();
    static std::string forAST(std::string call);
    std::string returnValue();
    std::string getReturnType();
    void analyseFunction();
    void argResolving();
    std::tuple<int, int, int> getInfo();
};

#endif // FUNCTION_H
