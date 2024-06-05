#include "CodeMap.h"
//#include "../../../Server/UserCode/usercode.h"

CodeMap::CodeMap() /*: ui(UserCode::getUserCode())*/
{
    code.push_back("#include <iostream>");
    code.push_back("");
    code.push_back("int main()");
    code.push_back("{");
    code.push_back("");
    code.push_back("}");
    //initUICode();

}

int CodeMap::getCodeSize()
{
    return code.size();
}

void CodeMap::setCode(const std::string& codeLine)
{
    code.push_back(codeLine);
}

std::string CodeMap::getCode(unsigned int lineNumber)
{
    return code[lineNumber];
}

void CodeMap::clearMap()
{
    code.clear();
    code.push_back("");
}

//void CodeMap::printCodeMap()
//{
//    int x = 0;
//    for (auto& each : code) {
//        std::cout << x << " " << each << std::endl;
//        ++x;
//    }
//}




