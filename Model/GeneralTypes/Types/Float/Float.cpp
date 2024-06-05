#include "Float.h"
Float::Float(std::string current_line)
{
    type = "float";
    sign = '+';
    size = std::to_string(sizeof(float)) + " byte";
    val = 0;
    if(current_line.find("float") != std::string::npos) {
        containsTypeInfo = true;
    }
    resolveExpression(current_line);
}

void Float::resolveExpression(std::string str)
{
    if (str.back() == ';' || str.back() == ',') {                  //removing the semicolon or comma
        str.pop_back();
    }
    std::vector<std::string> tokens = Tokenizing(str);
    size_t it = str.find_first_of("({");
    if (tokens[0] == "float") {
        name = tokens[1];
        if (str.find('=') == std::string::npos) { //if there is no '=' in the expression
            if (it == std::string::npos) { // and there is no initialization
                if (SC->getScopeIndex() == 0) {
                    value = '0';         //if the value located in global scope
                }
                else {
                    value = "Garbage";   //if the value located in some local scope
                }
                return;
            }
            else { //if there are braces
                str = str.substr(it);
                operator =(str);
            }
            it = name.find_first_of("{("); //separating the name from the value | float x(5); -> x
            name.erase(name.begin() + it, name.end());
        }
        else { // if there is '='
            size_t equal_pos = str.find('='); // finding the index of '='
            str = str.substr(equal_pos + 1); //slicing the string after the '='
            operator =(str);
        }
    }
}

void Float::resolveValue(std::string str)
{
    if(str.empty()) {
        value = "0";
        return;
    }
    std::ostringstream oss; //creating buffer object to get the correct form of the value
    unsigned long long ULL = 0;
    try {
        if(str.find('e') == std::string::npos && str.find('.') == std::string::npos || str.find('E') != std::string::npos) { //if the value type is unsigned long long | float x = 6456454545454155;
            ULL = std::stoull(str);
        }
        val = std::stof(str);
        oss << val;
        value = oss.str();
    } catch(std::invalid_argument& e) { //if there is a non-numeric value
        if(str == "true") {
            value = '1';
        } else if(str == "false") {
            value = '0';
        } else if(str[0] == '\'') {
            resolveChar(str);
        } else {
            value = SC->getValueByName(str).first; //the value is a name of other variable
            resolveValue(value);
        }
    } catch(std::out_of_range& e) {
        if(str.find('e') != std::string::npos || str.find('E') != std::string::npos || str.find('.') != std::string::npos) { //if the value is float type and greater than the maximum value of float
            value = "inf";
        }
        else { //if the value has type long long and is greater than long long maximum value
            QString qstr = QString::fromStdString(str); //casting std::string to Qstring for the further operations
            QTextStream stream(&qstr); //in this case QTextstream works more accurate than the stringstream object;
            stream >> ULL;
            val = ULL;
            oss << val;
            value = oss.str();
        }
    }
    if (sign == value[0]) {
        value.erase(0,1);
    } else if (value != "0" && sign == '-') {
        value.insert(value.begin(),sign);
    }
    sign = '+'; // reseting the sign value for that cases when a new object is not created |int x = -5; float f = -x;|
    size_t it = value.find(".");
    if (it != std::string::npos) {
        while(value.back() == '0' && value.find('e') == std::string::npos && value.find('E') == std::string::npos) { // 34.000000 -> 34, but not 1.234e+300 -> 1.234e+3
            value.pop_back();
        }
        if (value.back() == '.') {
            value.pop_back();
        }
    }
}


void Float::resolveChar(std::string str)
{
    if (str.size() <= 3) { //simple cases for exapmple 'a', 'g' ...
        int val = str[1];
        value = std::to_string(val);
    }
    else if (std::isdigit(str[2])) {
        std::string octalVal;
        size_t ind = str.find('\\');
        for (int i = ind + 1; std::isdigit(str[i]) && str[i] < '8'; ++i) { //when the char is initialized by octal number
            octalVal += str[i];
        }
        int val = std::stoi(octalVal, nullptr, 8);
        if (val <= 127 && val >= 0) {
            value = std::to_string(val);
        }
        else if (val > 127 && val < 256) {
            val -= 256;
            value = std::to_string(val);
        }
    }
    else if (str[2] == 'x') { //when the char is initialized by hexadecimal number
        std::string hexlVal;
        size_t ind = str.find('\\');
        for (int i = ind + 2; isHexDigit(str[i]); ++i) {
            hexlVal += str[i];
        }
        int val = std::stoi(hexlVal, nullptr, 16);
        if (val <= 127 && val >= 0) {
            value = std::to_string(val);
        }
        else if (val > 127 && val < 256) {
            val -= 256;
            value = std::to_string(val);
        }
    }
    else {
        char o = str[2]; //the symbol after the '\'
        if (o == '\'') {
            value = "39";
        } else if (o == '\"') {
            value = "34";
        } else if (o == '\?') {
            value = "63";
        } else if (o == '\\') {
            value = "92";
        } else if (o == 'a') {
            value = "7";
        } else if (o == 'b') {
            value = "8";
        } else if (o == 'f') {
            value = "12";
        } else if (o == 'n') {
            value = "10";
        } else if (o == 'r') {
            value = "13";
        } else if (o == 't') {
            value = "9";
        } else if (o == 'v') {
            value = "11";
        } else if (o == 'e' || o == 'E') {
            value = "27";
        }
    }

}

void Float::operator=(std::string str)
{
    while(str[0] == ' ') {
        str.erase(0,1);
    }
    if(str[0] == '{') {
        str = containsCurlyBraces(str);
    }
    str = simplify(str); //removing multi sign characters | "-+(-(-4) + (-(-5)" -> "-(4) + (5)"
    int count = std::count(str.begin(),str.end(),' '); //count of spaces in the expression
    if(!count) {
        if(str[0] == '-') {
            sign = '-';
            str.erase(0,1);
        }
        if(str[0] == '(') {
            str = containsOnlyBraces(str);
        }
    }
    else if(count) { //if there is a space
        complexInitialization(str); //float x = 3 * 7;
        str = value;
    }
    if(str[0] == '-') {
        sign = '-';
        str.erase(0,1);
    }
    resolveValue(str);
}

std::string Float::containsOnlyBraces(std::string str)
{
    size_t ind = str.rfind('(');
    str.erase(0, ind + 1);
    ind = str.find(')');               //clearing value from all braces
    str.erase(ind);
    return str;
}

std::string Float::containsCurlyBraces(std::string str)
{
    str.erase(0,1);
    str.pop_back();
    return str;
}

void Float::complexInitialization(std::string str)
{
    AST ob(str);
    str = std::to_string(double(ob));
    resolveValue(str);
}
bool Float::isHexDigit(char c)
{
    return (std::isdigit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'));
}

void Float::determineSign(std::string& str)
{
    for(int i = 0; i < str.size(); ++i) {
        if(str[i] == '-' && str[i-1] != 'e' && str[i-1] != 'E') {
            str.erase(i,1);
            --i;
            changeSign();
        }
        else if (str[i] == '+' && str[i-1] != 'e' && str[i-1] != 'E') {
            str.erase(i,1);
            --i;
        }
    }
}

void Float::changeSign()
{
    if (sign == '+') {
        sign = '-';
    }
    else {
        sign = '+';
    }
}

std::string Float::simplify(std::string str)
{
    std::vector<std::string> tokens = Tokenizing(str);
    std::string simple;
    for(int i = 0; i < tokens.size(); ++i) {
        sign = '+';
        if(tokens[i].size() > 1) {
        determineSign(tokens[i]);
        }
        if(sign == '-') {
            tokens[i].insert(tokens[i].begin(),'-');
        }
        simple += tokens[i];
        simple += ' ';
    }
    if(!simple.empty()) {
        simple.pop_back(); //removing the last space
    }
    return simple;
}
