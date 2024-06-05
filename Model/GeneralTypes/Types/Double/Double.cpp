#include "Double.h"

Double::Double(std::string current_line) : Type()
{
    if(current_line.back() == ';') {

        current_line.pop_back(); //removing the last semicolon
    }
    if(current_line.find("double") != std::string::npos) {
        containsTypeInfo = true;
    }

    this -> size = "8 byte"; //setting the size of variable
    this -> type = "double";
    isCalledAlready = {false};
    resolveExpression(current_line);  //right after creation current line needs to be resolved
}

Double::~Double() {}

void Double::resolveValue(std::string val)
{
  value = doubleCast(val);
}


void Double::resolveExpression(std::string str)
{
    std::vector<std::string> tokens = Tokenizing(str);

    if(tokens[0] == "double")
    {
        if(str.find(',') != std::string::npos && str.find('=') == std::string::npos)
        {
            std::string tmp = str.substr(str.find("double ") + 7);
            int i = 0;
            while(tmp[i] != '{' && tmp[i] != '(')
            {
                ++i;
            }
            std::string st = tmp;
            tmp = tmp.substr(i + 1, tmp.size() - i - 2);
            if(!isFunction(tmp))
            {   
                name = st.substr(0, i);
                std::vector<std::pair<double, std::string>> vec;
                AST(st.substr(i), vec);
                resolveValue(std::to_string(vec[vec.size() - 1].first));
                return;
            }
        }
        if(str.find('=') == std::string::npos)  //initialization with braces
        {
            if((tokens.size() > 3 ) && (str.find('*') != std::string::npos || str.find('/') != std::string::npos || str.find('+') != std::string::npos || str.find('-') != std::string::npos ||str.find(':') != std::string::npos || str.find('?') != std::string::npos ||
                                        str.find('^') != std::string::npos || str.find('%') != std::string::npos || str.find('<') != std::string::npos || str.find('>') != std::string::npos ||str.find('|') != std::string::npos || str.find('&') != std::string::npos))
            { //for double e(5 + 5 * 5);
                std::string val = str.substr(str.find("double ") + 7,str.size());
                int i = 0;
                while(val[i] != '(' && val[i] != '{')
                {
                    name += val[i];
                    ++i;
                }
                 val = val.erase(0,i);
                 if (val.front() == '{') {
                    val.pop_back();
                    val = val.substr(1);
                 }
                  value = toAST(val);
                  return;
            } else { //double x, double y(-789), double y{false}, double d(foo(7, 8))
                if(str.find('(') == std::string::npos && str.find('{') == std::string::npos)
                {
                    name = tokens[1];
                    value = "0";
                }
                else if(str.find('(') != std::string::npos && str.find('{') == std::string::npos)
                {
                    std::string tmp = str.substr(str.find("double ") + 7);
                    int i = 0;
                    while(tmp[i] != '(')
                    {
                        ++i;
                    }
                    tmp = tmp.substr(i + 1, tmp.size() - i - 2);
                    if(!isFunction(tmp))
                    {
                        tokens[1] = containsOnlyBraces(tokens[1]);
                        isCalledAlready = {false}; //for default working on the next call
                        resolveValue(tokens[1]);
                    } else {
                        name = tokens[1].substr(0, tokens[1].find('('));
                        resolveValue(CB ->processString(tmp));
                    }
                } else { // { || {(  //double x{(((4)))}
                    std::string tmp = str.substr(str.find("double ") + 7);
                    int i = 0;
                    while(tmp[i] != '{')
                    {
                        ++i;
                    }
                    tmp = tmp.substr(i + 1, tmp.size() - i - 2);
                    if(!isFunction(tmp))
                    {
                        tokens[1] = containsCurlyBraces(tokens[1]);
                        isCalledAlready = {false}; //for default working on the next call
                        resolveValue(tokens[1]);
                    } else {
                        name = tokens[1].substr(0, tokens[1].find('{'));
                        resolveValue(CB ->processString(tmp));
                    }
                }
            }
        }
        else if(str.find("=") != std::string::npos || str.find(',') != std::string::npos) //declarations or assignments    without checking tokens[0] == "double"
        {
            operator =(str);
        }
    }
    else if (tokens.size() == 1 && (tokens[0].find("++") != std::string::npos || tokens[0].find("--") != std::string::npos)) // ++x or x--
    {
        value = resolveOperation(tokens[0]);
    }
    else // x = f or x = 25
    {
        if (tokens[1] == "="){
            operator =(str);
        } else if (tokens[1] == "+="){
            operator +=(str);
        } else if (tokens[1] == "-=") {
            operator -=(str);
        } else if (tokens[1] == "*=") {
            operator *=(str);
        } else if (tokens[1] == "/=") {
            operator /=(str);
        }
        SC -> setValueByName(tokens[0], value);
    }
}

std::string Double::containsOnlyBraces(std::string unresolved_val)
{
    bool neg = false; //for check val is negative or not
    bool isdigit = false; //for check digit is a part of name or not
    if(unresolved_val[0] == '-' || unresolved_val[0] == '+') // double x = -789;
    {
        int i = 0;
        while(unresolved_val[i] == '-' || unresolved_val[i] == '+' || unresolved_val[i] == '(') //for +-+-+-+-+-+-+-+-5;
        {
            if (unresolved_val[i] == '(') {
                ++i;
                continue;
            }
            if(unresolved_val[i] == '-'){
                neg = !neg;
            }
            ++i;
        }
        unresolved_val.erase(0, i);
        isdigit = !isdigit;
    }
    if(unresolved_val.back() == ')')
    {
        //double x(((-485)))
        int i = 0;
        while(unresolved_val[i] !='(')
        {
            if(std::isdigit(unresolved_val[i]) && isdigit) {
                break;
            }
            if(!isCalledAlready){
                name += unresolved_val[i];
            }
            ++i;
        }
        while(unresolved_val[i] == '(')
        {
            ++i;
        }

        unresolved_val = unresolved_val.substr(i);
        while(unresolved_val.back() == ')') //5)))
        {
            unresolved_val.pop_back();
        }
        // ((('a'))) -> 'a'
    } else { //for double d = (double(1.5));
        int i = 0;
        while(unresolved_val[i] !='(' && !std::isdigit(unresolved_val[i]))
        {

            ++i;
        }
        while(unresolved_val[i] =='(')
        {
            ++i;
        }
        unresolved_val = unresolved_val.substr(i);

    }
    if (neg) {
        unresolved_val = '-' + unresolved_val;
    }

    isCalledAlready = !isCalledAlready;

    return unresolved_val;
}


std::string Double::containsCurlyBraces(std::string unresolved_val) //can also contain (
{
    int ind  = 0;
    while(unresolved_val[ind] != '{' && unresolved_val[ind] != '(' && !(std::isdigit(unresolved_val[0])) && unresolved_val[0] != '-' && unresolved_val[0] != 39) // 39 for symbol ' and '-' for double d = (-45) //when calleed 2 times
    {
        if(!isCalledAlready){
            name += unresolved_val[ind];
        }
        ++ind;
    }
    unresolved_val = unresolved_val.substr(ind);

    //{(((6)))}
    if (!std::isdigit(unresolved_val[0]) && unresolved_val[0] != '-' && unresolved_val[0] != 39){ // 39 for symbol ' and '-' for double d = (-45)
        unresolved_val = unresolved_val.substr(1);

        if (!std::isdigit(unresolved_val.back())){
            unresolved_val.pop_back(); // {(((4)))
        }
    }
    while(unresolved_val.back() == ')' || unresolved_val.back() == '}')
    {
        unresolved_val.pop_back();
    }
    //(((4
    ind = 0;
    while(unresolved_val[ind] == '(' || unresolved_val[ind] == '{')
    {
        ++ind;
    }
    unresolved_val = unresolved_val.substr(ind);

    isCalledAlready = !isCalledAlready;

    return unresolved_val;
}

void Double::operator =(std::string str)
{
    std::vector<std::string> tokens = Tokenizing(str);
    if(tokens[0] == "double")
    {
        if(str.find(',') != std::string::npos) //Complex initialization case
        {
            std::string tmp = str.substr(str.find('=') + 1);
            if(!isFunction(tmp))
            {
                name = tokens[1];
                std::vector<std::pair<double, std::string>> vec;
                AST(tmp, vec);
                resolveValue(std::to_string(vec[vec.size() - 1].first));
                return;
            }
        }
        //tokens.size() > 4 is chain operation
        if((tokens.size() > 4 )&& (str.find('*') != std::string::npos || str.find('/') != std::string::npos || str.find('+') != std::string::npos || str.find('-') != std::string::npos || str.find(':') != std::string::npos || str.find('?') != std::string::npos ||
                                   str.find('^') != std::string::npos || str.find('%') != std::string::npos || str.find('<') != std::string::npos || str.find('>') != std::string::npos ||str.find('|') != std::string::npos || str.find('&') != std::string::npos))
        {
            name = tokens[1];
            std::string expression = str.substr(str.find('=') + 2,str.size());
            bool neg = containsMinus(expression);
            value = toAST(expression);
            if (neg) {
                value = '-' + value;
            }
            return;
        }

        if(tokens.size() >= 4)//double x = 6   or  double x = (152)  or  double x = {123}  or double x = double({14.2}) double x = double(int{(14)})
        {
            if(!isFunction(str.substr(str.find('=') + 1, str.size() - 1)))
            {
                name = tokens[1];
                containsAllBraces(tokens[3]);
            }
            else {
                name = tokens[1];
                resolveValue(CB ->processString(str.substr(str.find('=') + 1, str.size() - 1)));
            }
        }

    }
    else {
        if((tokens.size() > 3 ) && (str.find('*') != std::string::npos || str.find('/') != std::string::npos || str.find('+') != std::string::npos || str.find('-') != std::string::npos || str.find(':') != std::string::npos || str.find('?') != std::string::npos ||
                                    str.find('^') != std::string::npos || str.find('%') != std::string::npos || str.find('<') != std::string::npos || str.find('>') != std::string::npos ||str.find('|') != std::string::npos || str.find('&') != std::string::npos))
        {
            std::string expression = str.substr(str.find('=') + 2,str.size());
            bool neg = containsMinus(expression);
            value = toAST(expression);
            if (neg) {
                value = '-' + value;
            }
            return;
        } else {
            str = str.substr(str.find('=') + 2);
            if(isFunction(str)) //work only d = foo(7, 8)
            {
                name = tokens[1];
                resolveValue(CB ->processString(str));
            }
        }
        if (tokens.size() == 3) {
            if(!isFunction(tokens[2])){
                containsAllBraces(tokens[2]);
                value = resolveOperation(tokens[2]);
            } else {
                resolveValue(CB ->processString(tokens[2]));
            }

            return;
        }

        if(str.find(',') != std::string::npos) //Complex initialization case
        {
            std::string tmp = str.substr(str.find('=') + 1);
            if(!isFunction(tmp))
            {
                std::vector<std::pair<double, std::string>> vec;
                if(tmp.front() == '(')
                {
                    AST(tmp, vec);
                    resolveValue(std::to_string(vec[vec.size() - 1].first));
                } else {
                    tmp = "(" + tmp + ")";
                    AST(tmp, vec);
                    resolveValue(std::to_string(vec[0].first));
                }
            }
        }
    }
}


void Double::complexInitialization(std::string unresolved_val)  //b((((0), 0), 0, (1)))
{
    std::string resolved_val;
    if(unresolved_val.find('(') != std::string::npos || unresolved_val.find('{') != std::string::npos || unresolved_val.find(')') != std::string::npos || unresolved_val.find('}') != std::string::npos)
    {
        for (char c : unresolved_val)
        {
            if (c != '(' && c != ')' && c != '{' && c != '}')  //clearing all possible braces
            {
                resolved_val += c;
            }
         }
        resolved_val = toAST(resolved_val);
    }
    else { //b = 7, 8, 9;
        for(int i = 0; unresolved_val[i] != ','; ++i)
        {
            resolved_val += unresolved_val[i];
        }
    }
    resolved_val = toAST(resolved_val);
    resolveValue(resolved_val);
}

void Double::containsAllBraces(std::string& str)
{
    if(str.find('(') == std::string::npos  && str.find('{') == std::string::npos) //double x = -568 or double x = 's'
    {
        resolveValue(str);
    }
    else if(str.find('(') != std::string::npos  && str.find('{') == std::string::npos) //only (
    {
        str = containsOnlyBraces(str);
        if (str.find('(') != std::string::npos){
            str = containsOnlyBraces(str); //for double d = (double(0.5))
        }
        isCalledAlready = {false};
        resolveValue(str);
    }
    else if(str.find('{') != std::string::npos) // double x = {false}; double x = {(true)} //{ and also (
    {
        str = containsCurlyBraces(str);
        if (str.find('(') != std::string::npos  || str.find('{') != std::string::npos) {
            str = containsCurlyBraces(str); //for double d = {double(0.5)} or double d = (double{0.5})
        }
        isCalledAlready = {false};
        resolveValue(str);
    }
}

bool Double::containsMinus(std::string& expression)
{
    bool neg = false;
    if (expression.find('{') != std::string::npos) {
        expression = containsCurlyBraces(expression);
    }
    if (expression[0] == '-' && expression[1] == '(') {
        int i = 0;
        int j = 0;
        while(expression[i] == '-' || expression[i] == '+' || expression[i] == '(') //for +-+-+-+-+-+-+-+-5;
        {
            if (expression[i] == '(') {
                ++i;
                ++j;
                continue;
            }
            if ((expression[i] == '-' || expression[i] == '+') && expression[i + 1] != '(') {
                break;
            }
            if(expression[i] == '-'){
                neg = !neg;
            }
            ++i;
        }
        expression = expression.erase(0,i);
        while(j != 0)
        {
            expression = '(' + expression;
            --j;
        }
    }
    return neg;
}

std::string Double::toAST(std::string expression)
{
    AST exp(expression);
    double tmp = exp;
    std::string st = std::to_string(tmp);
    while(st.back() == '0')
    {
        st.pop_back();
    }
    if (st.back() == '.'){
        st.pop_back();
    }
    return st;
}

void Double::operator +=(std::string str)
{
    std::vector<std::string> tokens = Tokenizing(str);
    str = str.substr(str.find('=') + 2, str.size());
    value = toAST(SC -> getValueByName(tokens[0]).first + " + (" + str + ")");
}


void Double::operator -=(std::string str)
{
    std::vector<std::string> tokens = Tokenizing(str);
    str = str.substr(str.find('=') + 2, str.size());
    value = toAST(SC -> getValueByName(tokens[0]).first + " - (" + str + ")");
}

void Double::operator *=(std::string str)
{
    std::vector<std::string> tokens = Tokenizing(str);
    str = str.substr(str.find('=') + 2, str.size());
    value = toAST(SC -> getValueByName(tokens[0]).first + " * (" + str + ")");
}

void Double::operator /=(std::string str)
{
    std::vector<std::string> tokens = Tokenizing(str);
    str = str.substr(str.find('=') + 2, str.size());
    value = toAST(SC -> getValueByName(tokens[0]).first + " / (" + str + ")");
}

bool Double::isFunction(std::string str)
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


std::string Double::eraseBracesOfFunction(std::string str, int token_number)
{
    int index = 0;
    if(token_number == 1)
    {
        while(str[index] != '(' || str[index] != '{')
        {
            name += str[index];
            ++index;
        }
        str = str.substr(index);
    }
    if((str.front() == '(' && str.back() == ')') || (str.front() == '{' && str.back() == '}'))
    {
        while((str.front() == '(' && str.back() == ')') || (str.front() == '{' && str.back() == '}'))
        {
            ++index;
        }
        return str.substr(index, str.size() - index * 2); //returned function call
    }

    return str;
}
