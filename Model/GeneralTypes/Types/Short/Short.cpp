#include "Short.h"

Short::Short(std::string current_line)
{
    if (current_line.back() == ';') {
        current_line.pop_back();
    }

    if(current_line.find("short") != std::string::npos) {
        containsTypeInfo = true;
    }
    resolveExpression(current_line);
    this -> size = std::to_string(sizeof(short)) + " byte";
    this -> type = "short";
}

Short::~Short()
{

}

void Short::resolveExpression(std::string str)
{
    std::vector<std::string> tokens = Tokenizing(str);
    if (containsTypeInfo) {
        std::string tmp = "";
        if (tokens.size() > 2 && tokens[2] == "=") {
            this -> name = tokens[1];
            for (size_t i = 3; i < tokens.size(); ++i) {
                tmp += tokens[i] + " ";
            }
            tmp.pop_back();
            operator =(tmp);
        } else {
            std::string tmp = "";
            if (tokens.size() >= 2) {
                for (size_t i = 1; i < tokens.size(); ++i) {
                    tmp += tokens[i] + " ";
                }
                tmp.pop_back();
                size_t size = tmp.size();
                if (tmp[size - 1] == ')') {
                    tmp = containsOnlyBraces(tmp);
                    resolveValue(tmp);
                } else if (tmp[size - 1] == '}') {
                    tmp = containsCurlyBraces(tmp);
                    resolveValue(tmp);
                } else {
                    this -> name = tmp;
                    resolveValue("");
                }
            }
        }
    } else {
        name = tokens[0];
        std::string tmp = "";
        for (size_t i = 2; i < tokens.size(); ++i) {
            tmp += tokens[i] + " ";
        }
        tmp.pop_back();
        if (tmp.find(',') != std::string::npos && tmp[0] != '(' && countNonDefaultCtorFunctions(str) == 0) {
            std::istringstream iss(tmp);
            std::vector<std::string> vec;
            std::string token;

            while (std::getline(iss, token, ',')) {
                vec.push_back(token);
            }

            for (int i = 0; i < vec.size(); ++i) {
                if (i == 0){
                    operator =(vec[i]);
                    reserveOperators(name, tokens[1]);
                } else {
                    vec[i] = vec[i].substr(1);
                    operator =(vec[i]);
                }
            }
            return;
        }
        operator =(tmp);
        reserveOperators(name, tokens[1]);
    }
}

void Short::reserveOperators(std::string name, std::string op)
{
    std::string tmp = "";
    sign = false;
    if (op == "+="){
        tmp = operator +=(name);
    } else if (op == "-=") {
        tmp = operator -=(name);
    } else if (op == "*=") {
        tmp = operator *=(name);
    } else if (op == "/=") {
        tmp = operator /=(name);
    } else if (op == "%=") {
        tmp = operator %=(name);
    } else if (op == "|=") {
        tmp = operator |=(name);
    } else if (op == "&=") {
        tmp = operator &=(name);
    } else if (op == "^=") {
        tmp = operator ^=(name);
    } else if (op == "<<=") {
        tmp = operator <<=(name);
    } else if (op == ">>=") {
        tmp = operator >>=(name);
    } else {
        SC -> setValueByName(name, value);
        return;
    }
    if (sign) {
        value = "-";
    } else {
        value = "";
    }
    value += tmp;
    size_t f = value.find('.');
    value = value.substr(0, f);
    SC -> setValueByName(name, value);
}

void Short::operator =(std::string str)
{
    change_sign(str);
    if (isFunction(str)) {
        str = CB -> processString(str);
        change_sign(str);
    }
    if (str[0] == '(' || str[0] == '{') {
        while (str[0] == '(' || str[0] == '{') {
            str = str.substr(1);
            str.pop_back();
            change_sign(str);
        }
        if (isFunction(str)) {
            str = CB -> processString(str);
        }
        change_sign(str);
        if (str.find(' ') != std::string::npos) {
            str = resolveAST(str);
            resolveValue(str);
        } else {
            resolveValue(str);
        }
    } else if (str.find(' ') != std::string::npos) {
        str = resolveAST(str);
        resolveValue(str);
    } else {
        resolveValue(str);
    }
}

std::string Short::operator +=(std::string str)
{
    return resolveAST(SC -> getValueByName(str).first + " + " + value);
}

std::string Short::operator -=(std::string str)
{
    return resolveAST(SC -> getValueByName(str).first + " - " + value);
}

std::string Short::operator *=(std::string str)
{
    return resolveAST(SC -> getValueByName(str).first + " * " + value);
}

std::string Short::operator /=(std::string str)
{
    return resolveAST(SC -> getValueByName(str).first + " / " + value);
}

std::string Short::operator %=(std::string str)
{
    return resolveAST(SC -> getValueByName(str).first + " % " + value);
}

std::string Short::operator |=(std::string str)
{
    return resolveAST(SC -> getValueByName(str).first + " | " + value);
}

std::string Short::operator &=(std::string str)
{
    return resolveAST(SC -> getValueByName(str).first + " & " + value);
}

std::string Short::operator ^=(std::string str)
{
    return resolveAST(SC -> getValueByName(str).first + " ^ " + value);
}

std::string Short::operator <<=(std::string str)
{
    return resolveAST(SC -> getValueByName(str).first + " << " + value);
}

std::string Short::operator >>=(std::string str)
{
    return resolveAST(SC -> getValueByName(str).first + " >> " + value);
}

void Short::resolveValue(std::string str)
{
    if (std::isdigit(str[0])) {
        str = checkSize(str);
    } else if (str[0] == '.') {
        str = "0";
    } else if (str == "true") {
        str = "1";
    } else if (str == "false") {
        str = "0";
    } else if (str == "") {
         if (SC -> getScopeIndex() == 0) {
            str = "0";
         } else {
            str = "Garbage";
         }
    } else if (str[0] == '\'') {
        str = resolveApostrophe(str);
    } else {
        if ((str[0] == '+' && str[1] == '+') || (str[0] == '-' && str[1] == '-') ||
          (str[str.size() - 1] == '+' && str[str.size() - 2] == '+')  ||
          (str[str.size() - 1] == '-' && str[str.size() - 2] == '-') || str[0] == '!' || str[0] == '~') {
          str = resolveOperation(str);
          str = checkSize(str);
          if (sign) {
              value = "-";
          }
          value += str;
          return;
        }
        change_sign(str);
        std::vector<std::string> tmp = Tokenizing(SC -> getValueByName(str).second);
        if (tmp[0] == "char") {
            str = tmp[1];
        } else {
            str = SC -> getValueByName(str).first;
            str = checkSize(str);
        }
    }
    if (sign) {
        value = "-";
    }
    value += str;
}

std::string Short::resolveApostrophe(std::string str)
{
    if (str[1] == '\\') {
        if (str[2] == 'a') {
            str = "7";
        } else if (str[2] == 'b') {
            str = "8";
        } else if (str[2] == 't') {
            str = "9";
        } else if (str[2] == 'n') {
            str = "10";
        } else if (str[2] == 'v') {
            str = "11";
        } else if (str[2] == 'f') {
            str = "12";
        } else if (str[2] == 'r') {
            str = "13";
        } else if (str[2] == '\"') {
            str = "34";
        } else if (str[2] == '\'') {
            str = "39";
        } else if (str[2] == '\?') {
            str = "63";
        } else if (str[2] == '\\') {
            str = "92";
        } else if (str[2] == 'x') { //'\xFF' -> -1
            str = str.substr(3);
            str.pop_back();
            int x = std::stoi(str, 0, 16);
            if (x >= 128) {
                x = 256 - x;
                str = '-';
            }

            str = std::to_string(x);
        } else if (std::isdigit(str[2])) { // '\101' -> 65
            str = str.substr(2);
            str.pop_back();
            int x = std::stoi(str, 0, 8);
            if (x > 127) {
                x = 256 - x;
                str = '-';
            }
            str = std::to_string(x);
        }
    } else {
        short number = static_cast<short>(str[1]);
        str = std::to_string(number);
    }
    return str;
}




std::string Short::containsOnlyBraces(std::string str)
{
    size_t found1 = str.find('(');
    this -> name = str.substr(0, found1);
    str = str.substr(found1);
    while (str[0] == '(' && str[str.size() - 1] == ')') {
        str.pop_back();
        str.erase(0, 1);
        change_sign(str);
    }
    if (isFunction(str)) {
        str = CB -> processString(str);
        change_sign(str);
    }
    if (str.find(' ') != std::string::npos) {
        str = resolveAST(str);
    }
    return str;
}

std::string Short::containsCurlyBraces(std::string str)
{
    if (str[str.size() - 2] == '{') {
        this -> name = str.substr(0, str.size() - 2);
        str = "";
    } else {
        size_t found2 = str.find('{');
        this -> name = str.substr(0, found2);
        str = str.substr(found2 + 1);
        str.pop_back();
        change_sign(str);
        while (str[0] == '(' && str[str.size() - 1] == ')') {
            str.pop_back();
            str.erase(0, 1);
            change_sign(str);
        }
        if (isFunction(str)) {
            str = CB -> processString(str);
            change_sign(str);
        }
        if (str.find(' ') != std::string::npos) {
           str = resolveAST(str);
        }
    }
    return str;
}

void Short::complexInitialization(std::string str)
{

}

std::string Short::resolveAST(std::string str)
{
    AST ob(str);
    double x = ob;
    str = std::to_string(x);
    change_sign(str);
    return str;
}

std::string Short::checkSize(std::string str)
{
    change_sign(str);
    str = shortCast(str);
    change_sign(str);
    return str;
}

void Short::change_sign(std::string& str)
{
    if ((str[0] == '+' && str[1] == '+') || (str[0] == '-' && str[1] == '-')) {
        return;
    }
    while ((str[0] == '-' && str[1] == '+') || (str[0] == '+' && str[1] == '-')) {
        if ((str[0] == '-' && str[1] == '+') || (str[0] == '+' && str[1] == '-')) {
            if (sign){
                sign = false;
            } else {
                sign = true;
            }
            str = str.substr(1);
            str = str.substr(1);
        }
    }
    if (str[0] == '-' && str[1] == '('){
        if (sign){
            sign = false;
        } else {
            sign = true;
        }
        str = str.substr(1);
    } else if (str[0] == '+') {
        str = str.substr(1);
    } else if (str[0] == '-' && str.find(' ') == std::string::npos) {
        if (sign){
            sign = false;
        } else {
            sign = true;
        }
        str = str.substr(1);
    } else if (str[0] == '-') {
        std::string temp = str.substr(1, str.size() - 1);
        if (isFunction(temp)) {
            if (sign){
                sign = false;
            } else {
                sign = true;
            }
            str = str.substr(1);
        }
    }
}


bool Short::isFunction(std::string str) {
    std::regex pattern("\\b([a-zA-Z_]+)\\s*\\(\\s*([^()]*)\\s*\\)\\s*");

    std::smatch match;
    if (std::regex_match(str, match, pattern)) {
        std::string functionName = match[1];
        std::string parameters = match[2];
        if (!parameters.empty()) {
           if (parameters.find_first_not_of(" \t\n\v\f\r") != std::string::npos) {
               return true;
           }
        }
        if (functionName != "int" && functionName != "short" &&
           functionName != "double" && functionName != "float" &&
           functionName != "bool" && functionName != "char") {
            return true;
        }
    }
    return false;
}

int Short::countNonDefaultCtorFunctions(std::string str) {
    std::regex pattern("\\b([a-zA-Z_]+)\\s*\\(\\s*([^()]*)\\s*\\)\\s*");

    std::sregex_iterator iter(str.begin(), str.end(), pattern);
    std::sregex_iterator end;

    int count = 0;
    bool hasDefaultCtor = false;
    while (iter != end) {
        std::smatch match = *iter;
        std::string functionName = match[1];
        std::string parameters = match[2];
        if ((functionName == "int" || functionName == "short" ||
             functionName == "double" || functionName == "float" ||
             functionName == "bool" || functionName == "char") &&
            parameters.empty()) {
            hasDefaultCtor = true;
            break;
        }
        if (!parameters.empty()) {
            ++count;
        }
        ++iter;
    }

    return hasDefaultCtor ? 0 : count;
}

