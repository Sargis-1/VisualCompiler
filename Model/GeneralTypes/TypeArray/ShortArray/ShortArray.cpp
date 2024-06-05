#include "ShortArray.h"

ShortArray::ShortArray(std::string current_line) : flag {false}
{
    if (current_line.back() == ';') {
        current_line.pop_back();
    }
    this -> size = std::to_string(sizeof(short)) + " byte";
    this -> type = "short";
    resolveExpression(current_line);
}


void ShortArray::resolveExpression(std::string str)
{
    std::vector<std::string> tokens = Tokenizing(str);
    std::string tmp = "";
    for(int i = 1; i < tokens.size(); ++i) {
        tmp += tokens[i] + " ";
    }
    tmp.pop_back();
    int found = tmp.find('[');
    name = tmp.substr(0, found);
    tmp = tmp.substr(found);

    int found2 = tmp.find('[', found + 1);

    if (found2 != std::string::npos){
        foo(tmp);
    }

    if (tmp.back() == ']') {
        int s = resolveSize(tmp);
        ShowInUI(s);
    } else if (tmp.back() == '}') {
        std::string arrSize;
        int found = tmp.find(']');
        arrSize = tmp.substr(0, found + 1);
        int s = resolveSize(arrSize);

        int found1 = tmp.find('{');
        tmp = tmp.substr(found1);
        std::vector<std::string> result = resolveValue(tmp);
        ShowInUI(s, result);
    }
}

int ShortArray::resolveSize(std::string str)
{
    if (str[0] == '['){
        str = str.substr(1, str.size() - 2);
    }
    while (str[0] == '(' && str[str.size() - 1] == ')') {
        str.pop_back();
        str.erase(0, 1);
    }
    int resalt = 0;
//    if (str.find(' ') != std::string::npos) {
        AST ob(str);
        double x = ob;
        resalt = x;
//    } else if (isdigit(str[0])){
//        resalt = std::stoi(str);
//    } else {
//        str = SC -> getValueByName(str).first;
//        resalt = std::stoi(str);
//    }
    return resalt;
}

std::vector<std::string> ShortArray::resolveValue(std::string str)
{
    std::vector<std::string> vec;
    if (str == "{}"){
        return {};
    }
    if (str[0] == '{'){
        str = str.substr(1, str.size() - 2);
    }
    if (str[0] == '(' && str[str.size() - 1] == ')') {
        str = resolveAST(str);
        return {str};
    } else {
        std::istringstream iss(str);
        std::string token;

        while (std::getline(iss, token, ',')) {
            if (token[0] == ' ') {
                token = token.substr(1);
            }
            token = resolveAST(token);
            vec.push_back(token);
        }
    }
    return vec;
}

std::string ShortArray::resolveAST(std::string str)
{
    AST ob(str);
    double x = ob;
    str = std::to_string(x);
    int f = str.find('.');
    str = str.substr(0, f);
    return str;
}

void ShortArray::foo(std::string str)
{

}

void ShortArray::operator =(std::string str)
{

}

ShortArray::~ShortArray()
{

}
