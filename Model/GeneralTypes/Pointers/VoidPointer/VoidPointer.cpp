//#include "VoidPointer.h"
//#define NPOS -1

//VoidPointer::VoidPointer(std::string current_line)
//{
//    this -> type = "void_ptr" ;
//    if (current_line.back() == ';') {
//        current_line.pop_back(); //removing the last semicolon
//    }
//    resolveExpression(current_line); //right after creation current line needs to be resolved
//}

//VoidPointer::~VoidPointer()
//{

//}

//void VoidPointer::resolveValue(std::string val)
//{
//    if (val == "" || val == "NULL" || val == "nullptr" || val == "0") {
//        value = "0";
//        return;
//    } else if (val[0] == '&') { //val = &xxx
//        val.erase(0, 1);
//        value = SC -> getAddressByName(val).first;
//    } else {
//        value = SC -> getValueByName(val).first;
//    }
//}

//void VoidPointer::resolveExpression(std::string str)
//{
//    std::vector<std::string> tokens = Tokenizing(str);
//    if (tokens[0] == "void") {
//        if (str.find(',') != NPOS) {
//            operator=(str); //complex initialization case
//        }
//    }

//    if (tokens[0] == "void" && str.find('=') == NPOS) { //initialization with braces
//        if (tokens.size() == 2) { //void *x, void *y(NULL), void *y{nullptr}
//            if (str.find('(') == NPOS && str.find('{') == NPOS) { //void *p;
//                name = tokens[1];
//                while(name.front() == '*')
//                {
//                    name = name.erase(0,1);
//                }
//                value = "0";
//            } else if (str.find('(') != NPOS && str.find('{') == NPOS) {
//                tokens[1] = containsOnlyBraces(tokens[1]);
//                resolveValue(tokens[1]);
//            } else { // { || {(  //void* x{(((4)))}
//                tokens[1] = containsCurlyBraces(tokens[1]);
//                resolveValue(tokens[1]);
//            }
//        }
//    } else if (str.find("=") != NPOS) { //declarations or assignments
//        operator=(str);
//    }
//}

//std::string VoidPointer::containsOnlyBraces(std::string unresolved_val)
//{
//    if (unresolved_val.back() == ')') {
//        //x(((-485)))
//        int i = 0;
//        while (unresolved_val[i] !='(') {
//            name += unresolved_val[i];
//            ++i;
//        }

//        while (unresolved_val[i] == '(') {
//            ++i;
//        }

//        unresolved_val = unresolved_val.substr(i); //5)))
//        while (unresolved_val.back() == ')') {
//            unresolved_val.pop_back();
//        }
//        // ((('a'))) -> 'a' ((((((true))))) - > true
//    }
//    while(name.front() == '*')
//    {
//        name = name.erase(0,1);
//    }
//    return unresolved_val;
//}

//std::string VoidPointer::containsCurlyBraces(std::string unresolved_val)
//{
//    int ind  = 0;
//    while (unresolved_val[ind] != '{') {
//        name += unresolved_val[ind];
//        ++ind;
//    }

//    unresolved_val = unresolved_val.substr(ind);
//    if (unresolved_val.size() == 2) {
//        //value = "0";
//        return "";
//    }
//    //{(((6)))}
//    unresolved_val = unresolved_val.substr(1);

//    unresolved_val.pop_back(); // {(((4)))

//    while (unresolved_val.back() == ')') {
//        unresolved_val.pop_back();
//    }
//    //(((4
//    ind = 0;
//    while (unresolved_val[ind] == '(') {
//        ++ind;
//    }

//    unresolved_val = unresolved_val.substr(ind);
//    while(name.front() == '*')
//    {
//        name = name.substr(0,1);
//    }
//    return unresolved_val;
//}

//void VoidPointer::operator=(std::string str)
//{
//    std::vector<std::string> tokens = Tokenizing(str);
//    if (tokens[0] == "void") {
//        //Complex initialization case
//        if (str.find(',') != NPOS) {
//            if (str.find('{') != NPOS) {
//                 name = tokens[1].substr(0,tokens[1].find('{'));
//            } else {
//                name = tokens[1].substr(0,tokens[1].find('('));
//            }
//            while(name.front() == '*')
//            {
//                name = name.erase(0,1);
//            }
//            complexInitialization(tokens[tokens.size() - 1]);
//        } else if (tokens.size() == 4) {
//            name = tokens[1];
//            while(name.front() == '*')
//            {
//                name = name.erase(0,1);
//            }
//            if (str.find('(') == NPOS  && str.find('{') == NPOS) {
//                resolveValue(tokens[3]);
//            } else if (str.find('(') != NPOS  && str.find('{') == NPOS) {
//                tokens[3] = containsOnlyBraces(tokens[3]);
//                resolveValue(tokens[3]);
//            } else if (str.find('{') != NPOS) {
//                tokens[3] = containsCurlyBraces(tokens[3]);
//                resolveValue(tokens[3]);
//            }
//        }
//    }
//}

//void VoidPointer::complexInitialization(std::string unresolved_val)  //b((((0), 0), 0, (1)))
//{
//    std::string resolved_val;
//    for (char c : unresolved_val) {
//        if (c != '(' && c != ')' && c != '{' && c != '}') {
//            resolved_val += c;
//        }
//    }
//    resolveValue(resolved_val);
//}
