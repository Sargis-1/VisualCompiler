#include "DoubleArray.h"
#include <string>

DoubleArray::DoubleArray(std::string codeLine)
{
    if(codeLine.back() == ';') {

        codeLine.pop_back(); //removing the last semicolon
    }
    if(codeLine.find("double") != std::string::npos) {
        containsTypeInfo = true;
    }
    resolveExpression(codeLine);
}

DoubleArray::~DoubleArray()
{

}

void DoubleArray::resolveExpression(std::string unresolved_val)
{
    if(unresolved_val.find('=') != std::string::npos)
    {
        operator =(unresolved_val);
        return;
    }
    std::vector<std::string> tokens = Tokenizing(unresolved_val);
    if(tokens[0] == "double")
    {
        int i = 0;
        while(tokens[1][i])
        {
            name += tokens[1][i];
            ++i;
        }

    }
}

void DoubleArray::operator =(std::string unresolved_val)
{

}
