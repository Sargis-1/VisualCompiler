#ifndef CONTROLBLOCK_H
#define CONTROLBLOCK_H
#include "../../Model/Include/Enums/returnType.h"
#include "../../Model/Scope/scope.h"
#include "../Ram/RamController/RamController.h"
#include "../UserCode/usercode.h"
#include "../../Model/GeneralTypes/TypeController/TypeController.h"
//#include "../../Model/GeneralTypes/Pointers/VoidPointer/VoidPointer.h"
//ControlBlock is used to resolve currenct line, accepted from source code, send it to according type files(int, double, char, conditions resolver, function resolver, loops resolver)
//Here Singleton pattern is used

class ControlBlock : public Resetable {
public:
    returnType ControllerHelper(int codeLine); //called from Controller to resolve string until main function
    std::string processString(int& lineNumber, std::string code = "", bool arrowFlag = true);//new string processing function, will replace previous version
    std::string processString(std::string code);
    void addnewScope(bool isFunction = false);
    void removeLastScope(); //Removes last created scope
    void removeLastFunctionScope();//Removes last opened scope with its nested scopes

    void changeExecState(bool startClicked = false, bool stopClicked = false);
    void setPreMain(std::vector<std::pair<int, int>> preMain);

    void enableIconColor(int lineNumber);//enables -> icon color if needed
    void disableIconColor(int lineNumber);//disables -> icon color if needed

    static ControlBlock* getControlBlock(); //Method to get ControlBlock instance
    ~ControlBlock() = default; //Dtor

private:
    ControlBlock(); //Private ctor to enforce Singleton pattern

    //helpers
    bool isFunctionDeclaration(std::string& str); //Differentiates function and variable declarations
    bool isFunctionDefinition(std::string& str); //Differentiates function definitions
    void resolveDeclaration(const std::string& type, const std::string& name, const std::string& declaration); //Distinguish between function and variable declarations and handle them
    std::string resolveStatment(const std::string& token, const std::string& statement, int& lineNumber);//resolves conditions and loops
    void resolveAssignment(const std::string& assign, const std::string& declaration);//resolves assignment
    void resolveFuncDecl(const std::string& secondToken, const std::string& declaration);//resolves function declarations in function scope
    void resolveUnaryOperators(const std::string& expression, const std::string& declaration);//resolves unary operator calls, like ++x or !x
    int findInPreMain(int codeLine);//checks whether a string is a function and returns the number of strings to skip (global space)
    std::string createFunctionObject(const std::string& codeLine);//creates function object
    std::string createFunctionObject(const std::string& codeLine, int& lineNumber);//creates function object
    std::string creatMainFunctionObject(int& lineNumber);
    void timeDelay(int mSec = 3500);

    void update() override;

    //members
    bool startClicked;
    bool stopClicked;
    QTimer* timer;
    QEventLoop* loop;
    static ControlBlock* cbinstance; //Pointer to instance of this class
    RamController* cbRC; //RamController pointer to change somthing on Ui if needed
    UserCode* cbUC;
    Scope* scope;//Scope pointer to control scopes
    std::vector<std::string> generalTypes;
    std::vector<std::string> statements;
    std::vector<std::pair<int, int>> preMain;
};

#endif // CONTROLBLOCK_H
