#include "../../../../Server/Ram/RamController/RamController.h"
#include "Char.h"

Char::Char(std::string current_line)
{
    this -> size = std::to_string(sizeof(char)) + " byte";
    this -> type = "char ";
    if (current_line.back() == ';') {
        current_line.pop_back();  //removing the last semicolon
    }
    if (current_line.find("char") != std::string::npos) {
        containsTypeInfo = true;
    }
    resolveExpression(current_line);
}

Char::~Char()
{

}

void Char::resolveExpression(std::string str)
{
    std::vector<std::string> tokens = Tokenizing(str);
    std::string tmp = "";
    if (containsTypeInfo) {
        if (tokens.size() > 2 && tokens[2] == "=") {
            this -> name = tokens[1];
            for (size_t i = 3; i < tokens.size(); ++i) {
                tmp += tokens[i] + " ";
            }
            tmp.pop_back();
            operator=(tmp);
        } else if (tokens.size() >= 2) { // char x; or char c('o'); or char c{'p'};
            std::string tmp = "";
            for (size_t i = 1; i < tokens.size(); ++i) {
                tmp += tokens[i] + " ";
            }
            tmp.pop_back();
            if (tmp[tmp.size() - 1] == ')') {
                tmp = containsOnlyBraces(tmp); // call this function if we have ()
                resolveValue(tmp);
            } else if (tmp[tmp.size() - 1] == '}') {
                tmp = containsCurlyBraces(tmp); // call this function if we have {}
                resolveValue(tmp);
            } else {
                name = tmp;
                tmp = "";
                resolveValue(tmp);
            }
        }
    } else {

        for (size_t i = 2; i < tokens.size(); ++i) {
            tmp += tokens[i] + " ";
        }
        tmp.pop_back();
        operator=(tmp);
        if (tokens[1] == "+=") { // t += y;
            tmp = charCast(operator+= (tokens[0]));
        } else if (tokens[1] == "-=") {
            tmp = charCast(operator-= (tokens[0]));
        } else if (tokens[1] == "*=") {
            tmp = charCast(operator*= (tokens[0]));
        } else if (tokens[1] == "/=") {
            tmp = charCast(operator/= (tokens[0]));
        } else if (tokens[1] == "%=") {
            tmp = charCast(operator%= (tokens[0]));
        } else if (tokens[1] == "|=") {
            tmp = charCast(operator|= (tokens[0]));
        } else if (tokens[1] == "&=") {
            tmp = charCast(operator&= (tokens[0]));
        } else if (tokens[1] == "^=") {
            tmp = charCast(operator^= (tokens[0]));
        } else if (tokens[1] == "<<=") {
            tmp = charCast(operator<<= (tokens[0]));
        } else if (tokens[1] == ">>=") {
            tmp = charCast(operator>>= (tokens[0]));
        } else {
            SC -> setValueByName(tokens[0], this -> value);
            return;
        }
        if (sign) {
            value = "Garbage";
        } else {
            value = tmp;
        }
         SC -> setValueByName(tokens[0], tmp);
    }
}

void Char::resolveValue(std::string str)
{
    if (sign) { // for example char x = -7 or -s
        value = "Garbage";
        type += "-" + str;
        return;
    }
    if (str == "true") {
            value = "SOH"; // in ASCII 1 -> STAND OF HEADING
            this -> type += "1";
            return;
    } else if (str == "false") {
            value = "NULL"; // in ASCII 0 -> NULL
            this -> type += "0";
            return;
    }
    bool flag = std::isdigit(str[0]);
    if (flag) { // char a = 8;
        type += str;
        value = charCast(str);
    } else if (str == "") {
        if (SC -> getScopeIndex() == 0) { // if true -> glogal
            value = "0";
        } else {
            value = "Garbage"; // local
        }
    } else if (str[0] == '\'') { // char c = '\a'
        if (str[1] == '\\') { // for example char t = '\a'
            value = str;
            if (str[2] == 'a') {
                this -> type += "7";
            } else if (str[2] == 'b') {
                this -> type += "8";
            } else if (str[2] == 't') {
                this -> type += "9";
            } else if (str[2] == 'n') {
                this -> type += "10";
            } else if (str[2] == 'v') {
                this -> type += "11";
            } else if (str[2] == 'f') {
                this -> type += "12";
            } else if (str[2] == 'r') {
                this -> type += "13";
            }
         } else if (str[2] == 'x' && str[1] == '\\') { //'\xFF' -> -1
                str = str.substr(3);
                str.pop_back(); // delete '
                if (str[0] < '8') {
                    int x = std::stoi(str, 0, 16);
                    this -> type += std::to_string(x);
                    value += "'" + std::string(1, static_cast<char>(x)) + "'";
                } else {
                    value = "Garbage";
                }
         } else if (std::isdigit(str[2]) && str[1] == '\\') { // '\101' -> 65
                str = str.substr(2);
                str.pop_back();
                if (str[0] < '4') {
                    int x = std::stoi(str, 0, 8);
                    this -> type += std::to_string(x);
                    value += "'" + std::string(1, static_cast<char>(x)) + "'";
                } else {
                    value = "Garbage";
                }
         } else if (str[0] == '\'' && str.size() > 2) {
            value = "'" + std::string(1, str[str.size() - 2]) + "'";// if str is symbol char c = 'dsss';
            int x = static_cast<int>(value[1]);
            this -> type += std::to_string(x);
         } else {
            value = str; // if str is symbol char c = 'd';
            int x = static_cast<int>(value[1]);
            this -> type += std::to_string(x);
         }
    } else {
        if ((str[0] == '+' && str[1] == '+') ||  (str[0] == '-' && str[1] == '-') ||
           (str[str.size() - 1] == '+' && str[str.size() - 2] == '+') ||
           (str[str.size() - 1] == '-' && str[str.size() - 2] == '-') || str[0] == '!' || str[0] == '~') { // ++x
            str = charCast(resolveOperation(str));
            value = str;
            return;
        }
        str = SC -> getValueByName(str).first; // char c = u;
        resolveValue(str);
        if (this -> type.find("char ") != std::string::npos) {
            this -> type += SC -> getValueByName(str).second;
        }

    }
}


void Char::operator= (std::string str)
{
    size_t size = str.size();
    sign_helper(str); // if we have expression with sign
    if (str[0] == '(' || str[0] == '{') {
        while (str[0] == '(' || str[0] == '{') {
            str = str.substr(1);
            str.pop_back();
            sign_helper(str);
        }
        if (str.find(' ') != std::string::npos) {
            str = resolve_ast(str);
            resolveValue(str);
            return;
        } else {
            resolveValue(str);
        }
    } else if (str.find(' ') != std::string::npos) { //if we have arithmetic expression
        str = resolve_ast(str);
        resolveValue(str);
    } else {
        resolveValue(str);
    }
}

std::string Char::operator+= (std::string str)
{
    str = get_value(str);
    str = resolve_ast(str + " + " + char_cast_to_int(value));
    return str;
}

std::string Char::operator-= (std::string str)
{
    str = get_value(str);
    str = resolve_ast(str + " - " + char_cast_to_int(value));
    return str;
}

std::string Char::operator*= (std::string str)
{
    str = get_value(str);
    str = resolve_ast(str + " * " + char_cast_to_int(value));
    return str;
}

std::string Char::operator/= (std::string str)
{
    str = get_value(str);
    str = resolve_ast(str + " / " + char_cast_to_int(value));
    return str;
}

std::string Char::operator%= (std::string str)
{
    str = get_value(str);
    str = resolve_ast(str + " % " + char_cast_to_int(value));
    return str;
}

std::string Char::operator|= (std::string str)
{
    str = get_value(str);
    str = resolve_ast(str + " | " + char_cast_to_int(value));
    return str;
}

std::string Char::operator&= (std::string str)
{
    str = get_value(str);
    str = resolve_ast(str + " & " + char_cast_to_int(value));
    return str;
}

std::string Char::operator^= (std::string str)
{
    str = get_value(str);
    str = resolve_ast(str + " ^ " + char_cast_to_int(value));
    return str;
}

std::string Char::operator<<= (std::string str)
{
    str = get_value(str);
    str = resolve_ast(str + " << " + char_cast_to_int(value));
    return str;
}

std::string Char::operator>>= (std::string str)
{
    str = get_value(str);
    str = resolve_ast(str + " >> " + char_cast_to_int(value));
    return str;
}

std::string Char::containsOnlyBraces(std::string str) // char c((('o')))
{
    size_t found = str.find('(');
    name = str.substr(0, found);
    str = str.substr(found);
    while (str[str.size() - 1] == ')') {
        str.pop_back();
        str = str.substr(1);
        sign_helper(str);
    }
    if (str.find(' ') != std::string::npos) {  //  for example char c = (7 + 8); or char d = (3, 9, 87);
        str = resolve_ast(str);
    }
    return str;
}

std::string Char::containsCurlyBraces(std::string str) // char c{(('p'))}
{
    if (str[str.size() - 2] == '{') { // char t{}
        str.pop_back();
        str.pop_back();
        name = str;
        str = "";
    } else {
        size_t found = str.find('{');
        name = str.substr(0, found);
        str = str.substr(found);
        sign_helper(str);
        while (str[str.size() - 1] == '}' || str[str.size() - 1] == ')') {
           str.pop_back();
           str = str.substr(1);
           sign_helper(str);
        }
        if (str.find(' ') != std::string::npos) { //  for example char c = (7 + 8); or char d = (3, 9, 87);
            str = resolve_ast(str);
        }
    }
    return str;
}

void Char::sign_helper(std::string& str)
{
    if ((str[0] == '+' && str[1] == '+') || (str[0] == '-' && str[1] == '-')) {
            return;
    }

    while ((str[0] == '-' && str[1] == '+') || (str[0] == '+' && str[1] == '-')) { // +-+-+-(56);
        if ((str[0] == '-' && str[1] == '+') || (str[0] == '+' && str[1] == '-')) {
            if (sign) {
                sign = false;
            } else {
                sign = true;
            }
            str = str.substr(1);
            str = str.substr(1);
        }
    }
    if (str[0] == '-' && str[1] == '(') { // char x = -(5);
        if (sign) {
            sign = false;
        } else {
            sign = true;
        }
        str = str.substr(1);
    } else if (str[0] == '+') { // char d = +5;
        str = str.substr(1);
    } else if (str[0] == '-' && str.find(' ') == std::string::npos) { // char k = -7 + 10;
        if (sign) {
            sign = false;
        } else {
            sign = true;
        }
        str = str.substr(1);
    }
}

std::string Char::resolve_ast(std::string str)  // Arithmetic expression (+, -, *, %, /) and ','
{
    AST obj(str);
    str = std::to_string(double(obj));
    str = str.substr(0, str.find('.'));
    sign_helper(str);
    return str;
}

std::string Char::get_value(std::string str)
{
    if ((SC -> getValueByName(str).first) == "Garbage") {
        std::vector<std::string> vec = Tokenizing(SC -> getValueByName(str).second);
        str = vec[vec.size() - 1];
    } else {
        str = SC -> getValueByName(str).first;
        str = char_cast_to_int(str);
    }
    return str;
}
void Char::complexInitialization(std::string str) // remember
{

}


