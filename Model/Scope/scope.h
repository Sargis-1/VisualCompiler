
#ifndef SCOPE_H
#define SCOPE_H
#include "../../Server/Ram/RamController/RamController.h"

//For every function, Condition statement, even for Global scope, Scope object will create new currentScope which will hold start indexes
//Scope class is singlton
class Scope : public Resetable {//inherits from Resetable to be notified when reset is clicked
public:
    static Scope* getScope();
    ~Scope();
    void pushNewScope(bool isFunction = false); //Adds new currentScope in scopes vector
    void popLastScope(); //Removes last scope from scopes vector
    void popFunctionScope();//Removes all opened scopes starting from last function
    short getScopeIndex();//Returns last scope index
    std::pair<std::string, std::string> getAddressByName(const std::string& name);//Returns given variable address and type
    std::pair<std::string, std::string> getValueByName(const std::string& name); //Returns given variable value and type
    std::pair<std::string, std::string> getValueByAddress(const std::string& address); //Returns given value and type underlaying given address
    void setValueByName(const std::string& name, const std::string& value);//Resets the button text
    void changeType(const std::string& name, const std::string& type);//Changes the type of the given named variable


    //Implementation of a pure virtual method of the Resettable interface
    void update() override;

    class currentScope {
    public:
        currentScope(int stackStart, int readOnlystart, int dataStart, int bssStart);
        std::array<int, 4> segRangesStarts;
        bool isFunction; //Is used while searching data from scopes
    };

private:
    Scope();//Private ctor to enforce Singleton pattern
    static Scope* scopeInstance;
    RamController* RC;  //RamController* to release variables of the scope when it goes out of scope
    std::vector<currentScope> scopes; //Contains all the start points of segments
};

#endif // SCOPE_H
