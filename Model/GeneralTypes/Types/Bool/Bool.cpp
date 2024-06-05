#include "Bool.h"

Bool::Bool(std::string current_line)
{
    //std::cout << current_line << std::endl;
    size = std::to_string(sizeof(bool)) + " byte";
    this -> type = "bool";
    if(current_line.back() == ';' || current_line.back() == ',') {
         current_line.pop_back();
    }
    expression = current_line;
    resolveExpression(current_line);
}

Bool::~Bool()
{
}

void Bool::resolveExpression(std::string current_line)
{
    std::vector<std::string> tokens = Tokenizing(current_line);
     if (tokens[0] == "bool" && current_line.find('=') == std::string::npos) {
         containsTypeInfo = true;
        if (tokens.size() == 2) { //bool x, bool y(-789), bool y{false}
            if (current_line.find('(') == std::string::npos && current_line.find('{') == std::string::npos) {
                name = tokens[1];
                if (SC -> getScopeIndex() == 0) { //is located in global
                    value = "0";
                } else {
                    value = "Garbage";
                }
                return;
            } else if (current_line.find('(') != std::string::npos && current_line.find('{') == std::string::npos) {
                tokens[1] = containsOnlyBraces(tokens[1]);
                resolveValue(tokens[1]);
            } else { // { || {(  //bool x{(((4)))}
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
                AST ob('(' + tmp_str + ')');
                bool x = static_cast<double>(ob);
                resolveValue(std::to_string(x));

            } else { // { || {(  //bool x{(((4,7, 8, 9)))}
               std::string tmp_str = tokens[1];
               int ind = 2;
               while (tokens.size() != ind) {
                   tmp_str += ' ';
                   tmp_str += tokens[ind];
                   ++ind;
               }
                tmp_str = containsCurlyBraces(tmp_str);
                AST ob(tmp_str);
                bool x = static_cast<double>(ob);
                resolveValue(std::to_string(x));
            }
        }
    } else  if (current_line.find("=") != std::string::npos) { //declarations // without checking tokens[0] == "int"
        operator=(current_line);
    }
}

std::string Bool::containsCurlyBraces(std::string unresolved_val) //can also contain (
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
    unresolved_val = unresolved_val.substr(1);
    unresolved_val.pop_back();  // {(((4)))
    while (unresolved_val.back() == ')') {
        unresolved_val.pop_back();
    }
    //(((4
    ind = 0;
    while (unresolved_val[ind] == '(') {
        ++ind;
    }
    unresolved_val = unresolved_val.substr(ind);
    return unresolved_val;
}

std::string Bool::containsOnlyBraces(std::string unresolved_val)
{
    std::vector<std::string> tokens = Tokenizing(unresolved_val);
    if (unresolved_val.back() == ')') {
        //x(((-485)))
        int i = 0;
        while (unresolved_val[i] !='(') {
            if(tokens.size() != 4)
            name += unresolved_val[i];
            ++i;
        }

        while (unresolved_val[i] == '(') {
            ++i;
        }

        while (unresolved_val.back() == ')') { //5)))
            unresolved_val.pop_back();
        }

        unresolved_val = unresolved_val.substr(i);
        // if(tokens.size() != 1)  //(((1, 2), ((4,7), 8), 9)) //(((x,y), (z,m)))
        // {
        //     unresolved_val = resolvingRightHandOperand(unresolved_val);
        // }
        // ((('a'))) -> 'a' ((((((true))))) - > true
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

std::string Bool::resolvingRightHandOperand(std::string rhv)
{
    std::vector<std::string> tokens = Tokenizing(rhv);
    return tokens[tokens.size() - 1];
}

void Bool::resolveValue(std::string val)
{

    if (val == "") {
        value  = "0";
        return;
    }
    if (isFunction(val)) {
        value = CB -> processString(val);
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
        value = boolCast(value + val);
    } else if (val == "true") {
        value = "1";
    } else if (val == "false") {
        value = "0";
    } else if(val[0] == '!') {
        value = logicalNot(val.substr(1));
        //value = value.substr(0, value.find('.'));
    } else if (val[0] =='~') {
        value = bitwiseNot(val.substr(1));
        value = value.substr(0, value.find('.'));
    } else if (val.find("++") != std::string::npos){
        std::string increment_version;
        increment_version += val[0];
        if (increment_version[0] == '+') {
            // std::cout << "prefix called  ++" <<  std::endl;
            value = boolCast(prefixIncrement(val.substr(2)));
        } else {
            // std::cout << "postfix called  ++"<<  std::endl;
            value = boolCast(postfixIncrement(val.substr(0, val.size() - 2)));
        }
    } else { // val = 'a' val = x
        // std::cout << val <<  " static cast is working" << std::endl;
        if (val[0] == '\'') { // val = 'a'  val = '\0'
                if (val[1] == '\\' && val[2] == '0') { //only char '\0' sets bool variable as false
                    value = "0";
                } else {
                    value = "1";
                }
         } else {// char y = 'a'  int x = y
            bool x;
            try {
                x = static_cast<bool>(std::stoi(SC -> getValueByName(val).first));
//                if (x < 0 && value.size() != 0) {
//                    x = abs(x);
//                }
            } catch (std::invalid_argument& e) { //'-i  depq """"""NAYEL""""""
                resolveValue(SC -> getValueByName(val).first);
                return;
            } catch (std::out_of_range& e) { // //maxic mec linelu kam minic poqr linelu depq  """"""NAYEL""""""
                x = std::stoi(boolCast(SC -> getValueByName(val).first));
            }
            value = std::to_string(x);
        }
    }
//    if(value == std::to_string(int()) || value == "0")
//    {
//        value = "0";
//    } else {
//        value = "1";
//    }
}

void Bool::operator=(std::string str)
{
    std::vector<std::string> tokens = Tokenizing(str);
    if (tokens[0] == "bool") {
         //after adding modifiers for type, assignment of a variable name will be changed
         name = tokens[1];
         containsTypeInfo = true;
        if (tokens.size() == 4) {
           //int x = 6   or int x = ++k or  int x = (152)  or  int x = {123}  or int x = double({14.2})
           //int x = double(int{(14)}) int x = double({(14.2,15.4,19)}) these cases  also need to be handled

            if (str.find('(') == std::string::npos  && str.find('{') == std::string::npos) { //int x = -568 int x = 's'
               resolveValue(tokens[3]);
            } else if (str.find('(') != std::string::npos  && str.find('{') == std::string::npos) { //only (
                if (!isFunction(str)) {
                    tokens[3] = containsOnlyBraces(tokens[3]);
                }
                resolveValue(tokens[3]);
            } else if (str.find('{') != std::string::npos) { // int x = {false}; int x = {(true)} //{ and also (
                tokens[3] = containsCurlyBraces(tokens[3]);
                resolveValue(tokens[3]);
            }
        } else { //tokens.size() > 4` //int x = 12.5 + 17.5 + u;
            //needed to be handled cases like int x = double(9 + 15, int(35), 12 * double(int(12 + 46)));
            std::string temp_expr; //temp_expr = 12.5 + 17.5 + u
            for (int i = 3; i < tokens.size(); ++i)
            {
                temp_expr  += " " + tokens[i];
            }
            //there is no need to check appearance of a '{'
            if (!isFunction(str)) {
                resolveValue(CB -> processString(temp_expr + ";"));
            } else {
                AST ob(temp_expr);
                resolveValue(boolCast(std::to_string(static_cast<double>(ob))));
            }
        }
    } else { // x = .... this needs castTable
        if (tokens.size() >= 3) {   // x1 = y2,  x = 6, x = 15 + 16.2 + k,  x = p + v -2;
            if(tokens[1] == "=" ) {
                if (tokens.size() - 2  == 1){   //if tokens.size() == 3
                    if (std::isdigit(tokens[2][0])) { //x = 35352
                        SC -> setValueByName(tokens[0], boolCast(tokens[2]));
                    } else { // x = y
                        SC -> setValueByName(tokens[0],  boolCast(SC -> getValueByName(tokens[2]).first));
                    }
                } else { // if tokens.size() > 3 eg. x = 15 + 6.2 + k - b;
                    std::string temp_expression;
                    for (int i = 2; i < tokens.size(); ++i) {
                        temp_expression += " " + tokens[i];
                    }
                    AST ob(temp_expression);
                    SC -> setValueByName(tokens[0], boolCast(std::to_string(static_cast<double>(ob))));
                }
            } else { // x += y; ... //needed to be resolved x += ++y by ast
               SC -> setValueByName(tokens[0],  boolCast(callToAst(expression)));
        }
        }
    }
}

void Bool::complexInitialization(std::string str)
{

}

bool Bool::isFunction(std::string str)
{
    std::regex pattern("\\b([a-zA-Z]+)\\(.*");
    std::smatch match;
    if (std::regex_search(str, match, pattern)) {
        std::string functionName = match[1];
        if (functionName != "int" && functionName != "short" &&
            functionName != "double" && functionName != "float" &&
            functionName != "bool" && functionName != "char") {
            return true;
        }
    }
    return false;
}

// std::string Bool::operator +=(std::string str)
// {
//     return str;
// }
