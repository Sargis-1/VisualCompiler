#include "BaseType.h"

BaseType::BaseType()
    : name("") , value("") , size("") , RC(RamController::getRamController()) , SC(Scope::getScope()), containsTypeInfo(false),
      CB(ControlBlock::getControlBlock())
{
}

std::vector<std::string> BaseType::Tokenizing(std::string str)
{
    std::vector<std::string> tokens;
    std::string word;
    std::istringstream iss(str);
    while (iss >> word) {
        tokens.push_back(word);
    }
    return tokens;
}

void BaseType::ShowingObjectInUi(Segment segment, bool controlBssOrData)
{
  //  std::cout << "value: " << value << "  name: " << name << "  size: " << size << "  type: " << type << std::endl;
    if(SC -> getScopeIndex() == 0) { //is located in global
        if (controlBssOrData) {
            segment = Segment::Data;
        } else if (value == std::to_string(int()) || value == std::to_string(double()) || value == "NULL") {
            segment = Segment::Bss;
        } else { // is located in local
            segment = Segment::Data;
        }
    } else {
        segment = Segment::Stack;
    }

    if (segment == Segment::Stack) {
        RC -> stack -> pushSlot(value, name, size, type);
    } else if (segment == Segment::Heap) {
        RC -> heap -> pushSlot(value, name, size, type);
//    } else if (segment == Segment::SymTab) {
//        RC -> symtab -> pushSlot(value, name, size, type);
    } else if (segment == Segment::Readonly) {
        RC -> readonly -> pushSlot(value, name, size, type);
    } else if (segment == Segment::Bss) {
        RC -> bss -> pushSlot(value, name, size, type);
    } else if (segment == Segment::Data) {
        RC -> data -> pushSlot(value, name, size, type);
    }
}

BaseType::~BaseType()
{
    if (containsTypeInfo) {
        ShowingObjectInUi(segment);
    }
}

