#include "Int.h"
#include <regex>


Int::Int(std::string current_line)
{
    //std::cout << current_line << std::endl;
    size = std::to_string(sizeof(int)) + " byte";
    this -> type = "int";
    if(current_line.back() == ';' || current_line.back() == ',') {
        current_line.pop_back();
    }
    expression = current_line;
    resolveExpression(current_line);
}

Int::~Int()
{
}
void Int::resolveExpression(std::string current_line)
{
    std::vector<std::string> tokens = Tokenizing(current_line);
    if (tokens[0] == "int" && current_line.find('=') == std::string::npos) {
        containsTypeInfo = true;
        if (tokens.size() == 2) { //int x, int y(-789), int y{false}, int y(foo(5)), int y(foo())
            if (current_line.find('(') == std::string::npos && current_line.find('{') == std::string::npos) {
                name = tokens[1];
                if (SC -> getScopeIndex() == 0) { //is located in global
                    value = "0";
                } else {
                    value = "Garbage";
                }
                return;
            } else if (current_line.find('(') != std::string::npos && current_line.find('{') == std::string::npos) {
                //resolves function calls with no argument or with one argument  //int y(foo(5)), int y(foo())
                tokens[1] = containsOnlyBraces(tokens[1]);
                resolveValue(tokens[1]);
            } else { // { || {(  //int x{(((4)))}
                tokens[1] = containsCurlyBraces(tokens[1]);
                resolveValue(tokens[1]);
            }
        } else { //size > 2
            if (current_line.find('(') != std::string::npos && current_line.find('{') == std::string::npos) {
                std::string tmp_str = tokens[1];
                int i = 2;
                while (i !=tokens.size()) {
                    tmp_str += ' ';
                    tmp_str += tokens[i];
                    ++i;
                }
               tokens[1] = containsOnlyBraces(tmp_str);
                resolveValue(tokens[1]);
            } else { // { || {(  //int x{(((4)))}
                tokens[1] = containsCurlyBraces(tokens[1]);
                resolveValue(tokens[1]);
            }
        }
    } else  if (current_line.find("=") != std::string::npos) { //declarations // without checking tokens[0] == "int"
        // std::cout << "resolveExpr: " << current_line << std::endl;
        operator=(current_line);
    }
}

std::string Int::containsCurlyBraces(std::string unresolved_val) //can also contain (
{
    int ind  = 0;
    while (unresolved_val[ind] != '{') {
        name += unresolved_val[ind];
        ++ind;
    }
    unresolved_val = unresolved_val.substr(ind);
    if (unresolved_val.size() == 2) {
        //value = "0";
        return "";
    }
    //{(((6)))}
    // std::cout << "ContainsCURLYbraces 1 : " << unresolved_val << std::endl;
    unresolved_val = unresolved_val.substr(1);
    // std::cout << "ContainsCURLYbraces 2 : " << unresolved_val << std::endl;
    unresolved_val.pop_back();  // {(((4)))
    int count_of_braces = 0;
    while (unresolved_val[count_of_braces] == '(') {
        ++count_of_braces;
    }
    // std::cout << "ContainsCURLYbraces 4 : " << unresolved_val << std::endl;
    unresolved_val = unresolved_val.substr(count_of_braces);
    // std::cout << "ContainsCURLYbraces 5 : " << unresolved_val << std::endl;

    while (unresolved_val.back() == ')' && count_of_braces) {
        unresolved_val.pop_back();
        --count_of_braces;
    }
    // std::cout << "ContainsCURLYbraces 6 : " << unresolved_val << std::endl;
    return unresolved_val;
}

std::string Int::containsOnlyBraces(std::string unresolved_val)
{
    //std::cout << "ContainsOnlyBraces: " << unresolved_val << std::endl;
    std::vector<std::string> tokens = Tokenizing(unresolved_val);
    if (unresolved_val.back() == ')') {
        if (isFunction(unresolved_val)) {

        }
        //x(((-485)))
        int i = 0;
        while (unresolved_val[i] !='(') {
            if(tokens.size() != 4)
                name += unresolved_val[i];
            ++i;
        }
        int count_of_braces = 0;
        while (unresolved_val[i] == '(') {
            ++i;
            ++count_of_braces;
        }
        //   std::cout << "ContainsOnlyBraces 1 : " <<  count_of_braces << std::endl;
        while (unresolved_val.back() == ')' && count_of_braces) { //5)))
            unresolved_val.pop_back();
            --count_of_braces;
        }
        //  std::cout << "ContainsOnlyBraces 2 : " << unresolved_val << std::endl;
        //  std::cout << "ContainsOnlyBraces 3 : " <<  count_of_braces << std::endl;
        unresolved_val = unresolved_val.substr(i);
        //  std::cout << "ContainsOnlyBraces 4 : " << unresolved_val << std::endl;
    } else {
        int i = 0;
        while(unresolved_val[i] !='(')
        {
            ++i;
        }
        while(unresolved_val[i] =='(')
        {
            ++i;
        }
        unresolved_val = unresolved_val.substr(i);
    }
    return unresolved_val;
}

std::string Int::resolvingRightHandOperand(std::string rhv)
{
    std::vector<std::string> tokens = Tokenizing(rhv);
    return tokens[tokens.size() - 1];
}

void Int::resolveValue(std::string val)
{
    if(isFunction(val)) {
        //std::cout << "resolveValue: " << val << std::endl;
        value = CB -> processString(val);
        return;
    }

    if (val == "") {
        value  = "0";
        return;
    }
    if(val[0] == '-') { //val[0] == '+' ||
        value += val[0];
        val = val.substr(1);
    } // else if (val[0] == '+' && val[1]) {} etet menak plus e apa substr anel

    if (std::isdigit(val[0])) {
        while (!std::isdigit(val.back())) { //deleted f, F, ull, ll
            val.pop_back();
        }
        value = intCast(value + val);
    } else if (val == "true") {
        value += "1";
    } else if (val == "false") {
        value = "0";
    } else if(val[0] == '!') {
        if(val.back() == ';') {
            val.pop_back();
        }
        value = logicalNot(val.substr(1));
        value = value.substr(0, value.find('.'));
    } else if (val[0] =='~') {
        if(val.back() == ';') {
            val.pop_back();
        }
        value = bitwiseNot(val.substr(1));
        value = value.substr(0, value.find('.'));
    } else if (val.find("++") != std::string::npos){
        std::string increment_version;
        if(val.back() == ';') {
            val.pop_back();
        }
        increment_version += val[0];
        if (increment_version[0] == '+') {
            // std::cout << "prefix called  ++" <<  std::endl;
            value = intCast(prefixIncrement(val.substr(2)));
        } else {
            // std::cout << "postfix called  ++"<<  std::endl;
            value = intCast(postfixIncrement(val.substr(0, val.size() - 2)));
        }
    } else { // val = 'a' val = x
        // std::cout << val <<  " static cast is working" << std::endl;
        if (val[0] == '\'') {
            if (val[1] == '\\') {
                if (val[2] == 'a') {
                    value = "7";
                } else if (val[2] == 'b') {
                    value = "8";
                } else if (val[2] == 't') {
                    value = "9";
                } else if (val[2] == 'n') {
                    value = "10";
                } else if (val[2] == 'v') {
                    value = "11";
                } else if (val[2] == 'f') {
                    value = "12";
                } else if (val[2] == 'r') {
                    value = "13";
                } else if (val[2] == '\"') {
                    value = "34";
                } else if (val[2] == '\'') {
                    value = "39";
                } else if (val[2] == '\?') {
                    value = "63";
                } else if (val[2] == '\\') {
                    value = "92";
                } else if (val[2] == 'x') { //'\xFF' -> -1
                    val = val.substr(3);
                    val.pop_back();
                    int x = std::stoi(val, 0, 16);
                    if (x >= 128) {
                        x = 256 - x;
                        value += '-';
                    }
                    value += std::to_string(x);
                } else if (std::isdigit(val[2])) { // '\101' -> 65
                    val = val.substr(2);
                    val.pop_back();
                    int x = std::stoi(val, 0, 8);
                    if (x > 127) {
                        x = 256 - x;
                        value += '-';
                    }
                    value += std::to_string(x);
                }
            } else {
                int number = static_cast<int>(val[1]);
                value += std::to_string(number);
            }
        } else {// char y = 'a'  int x = y
            int x;
            try {
                x = static_cast<int>(std::stoi(SC -> getValueByName(val).first));
                if (x < 0 && value.size() != 0) {
                    x = abs(x);
                }
            } catch (std::invalid_argument& e) {
                resolveValue(SC -> getValueByName(val).first);
                return;
            } catch (std::out_of_range& e) {
                x = std::stoi(intCast(SC -> getValueByName(val).first));
            }
            value = std::to_string(x);
        }
    }
}

void Int::operator=(std::string str)
{
    std::vector<std::string> tokens = Tokenizing(str);
    if (tokens[0] == "int") {
        //after adding modifiers for type, assignment of a variable name will be changed
        name = tokens[1];
        containsTypeInfo = true;
        if (tokens.size() == 4) {
            //int x = 6   or int x = ++k or  int x = (152)  or  int x = {123}  or int x = double({14.2})
            //int x = double(int{(14)}) int x = double({(14.2,15.4,19)}) these cases  also need to be handled
            //int x = foo(), int x = foo(789), int x = -foor();
            if (str.find('(') == std::string::npos  && str.find('{') == std::string::npos) { //int x = -568 int x = 's'
                resolveValue(tokens[3]);
            } else if (str.find('(') != std::string::npos  && str.find('{') == std::string::npos) { //only (
                if (!isFunction(str)) {
                    //                  std::cout << "OPerator = 1: " << tokens[3] << std::endl;
                    tokens[3] = containsOnlyBraces(tokens[3]);
                    //                  std::cout << "OPerator = 2: " << tokens[3] << std::endl;
                }
                resolveValue(tokens[3]);
            } else if (str.find('{') != std::string::npos) { // int x = {false}; int x = {(true)} //{ and also (
                tokens[3] = containsCurlyBraces(tokens[3]);
                resolveValue(tokens[3]);
            }
        } else { //tokens.size() > 4` //int x = 12.5 + 17.5 + u; int x = foo(45, 78, 15 +7)
            //needed to be handled cases like int x = double(9 + 15, int(35), 12 * double(int(12 + 46)));
            std::string temp_expr; //temp_expr = 12.5 + 17.5 + u
            for (int i = 3; i < tokens.size(); ++i)
            {
                temp_expr  += " " + tokens[i];
            }
            //std::cout << "OPerator= 3: " << temp_expr << std::endl;
            if (isFunction(str)) {
                //std::cout << "OPerator= 4: " << temp_expr << std::endl;
                resolveValue(CB -> processString(temp_expr + ";"));
            } else {
                // std::vector<std::pair<double, std::string>> args;
                // AST ob(temp_expr, args);
                // std::cout << "is a function  2" << std::endl;
                // if(temp_expr[0] == '(') {
                //     resolveValue(intCast(std::to_string(args.back().first)));
                // } else {
                //     resolveValue(intCast(std::to_string(args.front().first)));
                // }
                //there is no need to check appearance of a '{'
                AST ob(temp_expr);
                resolveValue(intCast(std::to_string(static_cast<double>(ob))));
            }
        }
    } else { // x = .... this needs castTable
        if (tokens.size() >= 3) {   // x1 = y2,  x = 6, x = 15 + 16.2 + k,  x = p + v -2;
            if(tokens[1] == "=" ) {
                if (tokens.size() - 2  == 1){   //if tokens.size() == 3
                    if (std::isdigit(tokens[2][0])) { //x = 35352
                        SC -> setValueByName(tokens[0], intCast(tokens[2]));
                    } else { // x = y,  x = ++y, x = foo(), x = foo(y);
                        std::string str = tokens[2];
                        if ((str[0] == '+' && str[1] == '+') ||  (str[0] == '-' && str[1] == '-') ||
                            (str[str.size() - 1] == '+' && str[str.size() - 2] == '+') ||
                            (str[str.size() - 1] == '-' && str[str.size() - 2] == '-') || str[0] == '!' || str[0] == '~') { // ++x
                            str = intCast(resolveOperation(str));
                            SC -> setValueByName(tokens[0], str);
                        } else if (isFunction(tokens[2])) { //x = foo();
                            SC -> setValueByName(tokens[0], intCast(CB -> processString(tokens[2])));
                        } else {
                            SC -> setValueByName(tokens[0],  intCast(SC -> getValueByName(tokens[2]).first));
                        }
                    }
                } else { // if tokens.size() > 3 eg. x = 15 + 6.2 + k - b;
                    std::string temp_expression;
                    for (int i = 2; i < tokens.size(); ++i) {
                        temp_expression += " " + tokens[i];
                    }
                    if(isFunction(temp_expression)) {
                        SC -> setValueByName(tokens[0], intCast(CB -> processString(temp_expression + ";")));
                    } else {
                        std::vector<std::pair<double, std::string>> args;
                        AST ob(temp_expression, args);
                        if(temp_expression[0] == '(') {
                            SC -> setValueByName(tokens[0], intCast(std::to_string(args.back().first)));
                        } else {
                            SC -> setValueByName(tokens[0], intCast(std::to_string(args.front().first)));
                        }
                    }
                }
            } else { // x += y; ... //needed to be resolved x += ++y by ast
                SC -> setValueByName(tokens[0],  intCast(callToAst(expression)));
            }
        }
    }
}

void Int::complexInitialization(std::string str)
{

}

bool Int::isFunction(std::string expression)
{
    std::regex pattern("\\b([a-zA-Z]+)\\(.*");

    std::smatch match;
    if (std::regex_search(expression, match, pattern)) {
        std::string functionName = match[1];
        if (functionName != "int" && functionName != "short" &&
            functionName != "double" && functionName != "float" &&
            functionName != "bool" && functionName != "char") {
            return true;
        }
    }
    return false;
}

