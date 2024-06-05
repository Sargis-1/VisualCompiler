#include "scope.h"
#include "../../Model/Include/AST/AST.h"
Scope* Scope::scopeInstance = nullptr;

Scope::Scope() :
    RC(RamController::getRamController())
{

    //creates global scope
    scopes.push_back(currentScope(0, 0, 0, 0));
    scopes[0].isFunction = false;
}

Scope* Scope::getScope()
{

    //scope is singleton
    if (scopeInstance == nullptr) {
        scopeInstance = new Scope;
        provider -> subscribe(scopeInstance); //subscribes for updates
    }
    return scopeInstance;
}

//creates new scope with starts of all segments(which is calculated from ui)
void Scope::pushNewScope(bool isFunction)
{
    int stackStart = RC -> stack -> getSegmentSize();
    int readOnlyStart = RC ->readonly -> getSegmentSize();
    int dataStart = RC -> data -> getSegmentSize();
    int bssStart = RC -> bss -> getSegmentSize();
    scopes.push_back(currentScope(stackStart, readOnlyStart, dataStart, bssStart));
    scopes[scopes.size() - 1].isFunction = isFunction;
}

//deletes last scope from ui and scopes vector
//and resets addresses
void Scope::popLastScope()
{
    if (scopes.empty()) {
        return;
    }

    //reseting the addresses to their appropriate values
    size_t scopeIndex = scopes.size() - 1;

    RC -> stack -> resetAddresses(scopes[scopeIndex].segRangesStarts[0]);
    RC -> readonly -> resetAddresses(scopes[scopeIndex].segRangesStarts[1]);
    RC -> bss -> resetAddresses(scopes[scopeIndex].segRangesStarts[3]);
    RC -> data -> resetAddresses(scopes[scopeIndex].segRangesStarts[2]);

    //erasing slots from UI
    RC -> stack -> eraseStartingFrom(scopes[scopeIndex].segRangesStarts[0]);
    RC -> readonly -> eraseStartingFrom(scopes[scopeIndex].segRangesStarts[1]);
    RC -> bss -> eraseStartingFrom(scopes[scopeIndex].segRangesStarts[3]);
    RC -> data -> eraseStartingFrom(scopes[scopeIndex].segRangesStarts[2]);

    //when the last scope is deleted, the simtab is cleared
    if (scopeIndex == 0) {
        RC -> symtab -> eraseSymTab();
    }

    //deleting last scope information
    scopes.pop_back();
}

//removes all opened scopes starting from last scope in case of breaking conditions/loop
//void foo()
//{
//    while (condition) {
//        if (true) {
//            return;
//        }
//        ....
//    }
//}
void Scope::popFunctionScope()
{
    if (scopes.empty()) {
        return;
    }

    size_t scopeIndex = scopes.size() - 1;
    while (!scopes[scopeIndex].isFunction) {//find last funstion scope
        scopes.pop_back();
        --scopeIndex;
    }

    RC -> stack -> resetAddresses(scopes[scopeIndex].segRangesStarts[0]);
    RC -> readonly -> resetAddresses(scopes[scopeIndex].segRangesStarts[1]);
    RC -> bss -> resetAddresses(scopes[scopeIndex].segRangesStarts[3]);
    RC -> data -> resetAddresses(scopes[scopeIndex].segRangesStarts[2]);

    RC -> stack -> eraseStartingFrom(scopes[scopeIndex].segRangesStarts[0]);
    RC -> readonly -> eraseStartingFrom(scopes[scopeIndex].segRangesStarts[1]);
    RC -> bss -> eraseStartingFrom(scopes[scopeIndex].segRangesStarts[3]);
    RC -> data -> eraseStartingFrom(scopes[scopeIndex].segRangesStarts[2]);

    scopes.pop_back();
}

void Scope::update()
{
    if (!scopes.empty()) {
        scopes.clear();
    }

    //reseting all segments addresses to start addresses
    RC -> stack -> resetAddresses(0);
    RC -> readonly -> resetAddresses(0);
    RC -> bss -> resetAddresses(0);
    RC -> data -> resetAddresses(0);

    //creating new global scope after clearing all
    pushNewScope();
}

//returns last scope index
short Scope::getScopeIndex()
{
    return scopes.size() - 1;
}

//returns given variable address in first and type in second
std::pair<std::string, std::string> Scope::getAddressByName(const std::string& name)
{
    std::pair<std::string, std::string> returnedValue;
    std::string address;
    std::string type;
    int start = 0;
    int end = 0;

    for (int index = scopes.size() - 1; index >= 0; --index) {
        //if proccess is in function scope
        if(scopes[index].isFunction) {
            //Doesn't support heap and ReadOnly yet
            start = scopes[index].segRangesStarts[0];
            end = RC -> stack -> getSegmentSize();//calculates current segments end
            returnedValue = RC -> stack -> getAddress(name, start, end);
            address = returnedValue.first;
            type = returnedValue.second;

            if (address.empty()) {
                index = 1;//If value not found in last scope index will decremented in for loop and look at global scope
            } else {
                return returnedValue;
            }
        } else {
            if (index != 0) {//0 index is for global space
                start = scopes[index].segRangesStarts[0];
                end = RC -> stack -> getSegmentSize();//calculates current segment end
                returnedValue = RC -> stack -> getAddress(name, start, end);
                address = returnedValue.first;
                type = returnedValue.second;
            } else {
                end = RC -> data -> getSegmentSize();
                returnedValue = RC -> data -> getAddress(name, 0, end);
                address = returnedValue.first;
                type = returnedValue.second;
                if (address.empty()) {
                    end = RC -> bss -> getSegmentSize();
                    returnedValue = RC -> bss -> getAddress(name, 0, end);
                    address = returnedValue.first;
                    type = returnedValue.second;
                }
            }

            //if the value was found, it will be returned, otherwise iteration will be continued
            if (!address.empty()) {
                return returnedValue;
            }
        }
    }

    return {address, type}; //If value not found function will reach to this point and return empty strings
}

//returns given variable value in first and type in second
std::pair<std::string, std::string> Scope::getValueByName(const std::string& name)
{
    //std::cout << "Var to search = " << name  << std::endl;
    std::pair<std::string, std::string> returnedValue;
    std::string value;
    std::string type;
    int start = 0;
    int end = 0;

    for (int index = scopes.size() - 1; index >= 0; --index) {//std::cout << "getVAlueByName " << scopes.size() << std::endl;
        //if proccess in function scope
        //std::cout << "111111111111" << std::endl;
        if (scopes[index].isFunction) {
            //Doesn't support heap and ReadOnly yet
            start = scopes[index].segRangesStarts[0];
            end = RC -> stack -> getSegmentSize(); //calculates current segments end
            //std::cout << "Nnnname = " << name << std::endl;
            returnedValue = RC -> stack -> getValue(name, start, end);
            value = returnedValue.first;
            type = returnedValue.second;

            if (value.empty()) {
                index = 1; //If value not found index will decremented in for loop and look at global scope
            } else {
                return returnedValue;
            }
        } else {
            if (index != 0) {
                start = scopes[index].segRangesStarts[0];
                end = RC -> stack -> getSegmentSize();//calculates current segment end
                returnedValue = RC -> stack -> getValue(name, start, end);
            } else {
                end = RC -> data -> getSegmentSize();
                returnedValue = RC -> data -> getValue(name, 0, end);
                value = returnedValue.first;
                type = returnedValue.second;
                if (value.empty()) {
                    end = RC -> bss -> getSegmentSize();
                    returnedValue = RC -> bss -> getValue(name, 0, end);
                    value = returnedValue.first;
                    type = returnedValue.second;
                }
            }
            //if the value was found, it will be returned, otherwise iteration will be continued
            if (!value.empty()) {
                return returnedValue;
            }
        }
    }
    return returnedValue; //If value not found function will reach to this point and return empty strings
}

//returns the value stored under the given address
std::pair<std::string, std::string> Scope::getValueByAddress(const std::string& address)
{
    std::pair<std::string, std::string> returnedValue;

    unsigned int currAddress = std::stoul(address, nullptr, 16);
    //checks which segment the address is in
    if (currAddress >= std::stoul("0x00000000", nullptr, 16) && currAddress <= std::stoul("0x59999994", nullptr, 16)) {
        returnedValue = RC -> stack -> getValueByAddress(address);
    } else if (currAddress >= std::stoul("0xE666665D", nullptr, 16) && currAddress <= std::stoul("0xFFFFFFFF", nullptr, 16)) {
        returnedValue = RC -> bss -> getValueByAddress(address);
    } else if (currAddress >= std::stoul("0xCCCCCCC4", nullptr, 16) && currAddress <= std::stoul("0xE666665D", nullptr, 16)) {
        returnedValue = RC -> data -> getValueByAddress(address);
    } else if (currAddress >= std::stoul("0x59999994", nullptr, 16) && currAddress <= std::stoul("0xB333332A", nullptr, 16)) {
        //doesn't support yet
        //value = RC -> heap -> getValueByAddress(address);
    }

    return returnedValue; //If value not found function will reach to this point and return empty strings
}

//resets the given named variable value
void Scope::setValueByName(const std::string& name, const std::string& value)
{
    int start = 0;
    int end = 0;
    bool isValueChanged = false;

    for (int index = scopes.size() - 1; index >= 0; --index) {
        //if variable in function scope
        if (scopes[index].isFunction) {
            //Doesn't support heap and ReadOnly yet
            start = scopes[index].segRangesStarts[0];
            end = RC -> stack -> getSegmentSize(); //calculates current segments end
            isValueChanged = RC -> stack -> setValue(name, value, start, end);//returns true if value has been changed, false otherwise

            if (!isValueChanged) {
                index = 1; //If value not found index will decremented in for loop and look at the global scope
            } else {
                return;
            }
        } else {
            if (index != 0) {
                start = scopes[index].segRangesStarts[0];
                end = RC -> stack -> getSegmentSize();//calculates current segment end
                isValueChanged = RC -> stack -> setValue(name, value, start, end);
            } else {
                end = RC -> data -> getSegmentSize();
                isValueChanged = RC -> data -> setValue(name, value, 0, end);
                if (!isValueChanged) {
                    end = RC -> bss -> getSegmentSize();
                    isValueChanged = RC -> bss -> setValue(name, value, 0, end);
                }
            }

            if (isValueChanged) {
                return;
            }
        }
    }
}

//chenges the given named variable type
void Scope::changeType(const std::string& name, const std::string& type)
{
    int start = 0;
    int end = 0;
    bool isTypeChanged = false;

    for (int index = scopes.size() - 1; index >= 0; --index) {
        //if proccess in function scope
        if (scopes[index].isFunction) {
            //Doesn't support heap and ReadOnly yet
            start = scopes[index].segRangesStarts[0];
            end = RC -> stack -> getSegmentSize(); //calculates current segments end
            isTypeChanged = RC -> stack -> changeType(name, type, start, end);

            if (!isTypeChanged) {
                index = 1; //If value not found index will decremented in for loop and look at global scope
            } else {
                return;
            }
        } else {
            if (index != 0) {
                start = scopes[index].segRangesStarts[0];
                end = RC -> stack -> getSegmentSize();//calculates current segment end
                isTypeChanged = RC -> stack -> changeType(name, type, start, end);//returns true if type has been changed, false otherwise
            } else {
                end = RC -> data -> getSegmentSize();
                isTypeChanged = RC -> data -> changeType(name, type, start, end);
                if (!isTypeChanged) {
                    end = RC -> bss -> getSegmentSize();
                    isTypeChanged = RC -> bss -> changeType(name, type, start, end);
                }
            }

            if (isTypeChanged) {
                return;
            }
        }
    }
}

Scope::~Scope()
{
    this -> popLastScope();
}


Scope::currentScope::currentScope(int stackStart, int readOnlyStart, int dataStart, int bssStart)
{
    segRangesStarts[0] = stackStart;
    segRangesStarts[1] = readOnlyStart;
    segRangesStarts[2] = dataStart;
    segRangesStarts[3] = bssStart;
}
















