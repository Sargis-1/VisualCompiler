#include "Function.h"
#include <QTimer>

Function::Function(std::string call, std::vector<std::pair<double, std::string>>& args,std::string name)
    : call(call) ,returnType("") , CB(ControlBlock::getControlBlock()) , SC(Scope::getScope()) ,args(args), name(name) , RC(RamController::getRamController())
{
    size_t startPos = this -> call.find_first_not_of(" \t\n\r\f\v");
    this -> call = this -> call.erase(0,startPos);

    analyseFunction();
    argResolving();
    //executeFunction();
}

void Function::executeFunction()
{
//    std::cout << startLine << std::endl;
    for (i = startLine + 2; i < endLine; ++i) //i starts from startLine + 1 for skipping the prototype analysis
    {
        auto str = codeMap -> getCode(i);
        int indexReturn = str.find("return");
        if(indexReturn!= std::string::npos)
        {
            if(returnType == "void")
            {
                return;
            }
            else  //return a + b;
            {
                std::string expr = str.substr(indexReturn + sizeof("return"));
                expr = returnType + " tmp_value = " + expr;
                //std::cout << "expr str is: "<< expr << std::endl;
                CB -> processString(i, expr);
                return;
            }
        }
        if(str != "")
        CB -> processString(i);
        std::string currentCodeLine = codeMap -> getCode(i);
        std::string firstToken;
        std::istringstream iss(currentCodeLine);
        iss >> firstToken;
    }
}



void Function::analyseFunction()
{
    if(name == "")
    {
        name = call.substr(0,call.find('('));
    }
//no overloads handled

    info = RC -> symtab -> getInfoFunctionByName(name);
    int prototype_line = std::get<1>(info[0]);
    startLine = std::get<2>(info[0]);
    i = startLine;
    endLine = std::get<3>(info[0]);
    if(prototype_line != -1)
    {
        prototype = codeMap -> getCode(prototype_line);
    } else {
        prototype = codeMap -> getCode(startLine);
    }

    returnType = prototype.substr(0,prototype.find(name));
    while(returnType.back() == ' ')
    {
        returnType.pop_back();
    }

}

std::string Function::forAST(std::string call)
{
    if(call.back() == ';') {
        call.pop_back();
    }

    size_t pos = call.find('(');
    if (pos != std::string::npos) {  //saving only braces for passing them to AST
        // foo(1, 2, 3)  ---> (1, 2, 3)
        call.erase(0, pos);
    }

    return call;
}

void Function::argResolving()
{
    //just for now, arguments of main function are ignored
    if(name == "main") {
        return ;
    }

    call = forAST(call); // foo(1, 2, 3)  ---> call = (1, 2, 3)

    if(call != "()" && args.size() == 0) //if function has any arguments(not default) and more than one argument
    {
        AST(call,args);
    }

    std::string prototype = codeMap -> getCode(startLine);

    size_t pos1 = prototype.find('(');
    if (pos1 != std::string::npos) {//erasing the name and the first parentheses
        //void foo(int x, int z = 0) ---> int x, int z = 0)
       prototype.erase(0, pos1 + 1);
    }

    prototype.pop_back(); // int x, int z = 0
//    std::cout << prototype << std::endl;
//    exit(0);
    std::vector<std::string> parameters;
    std::stringstream ss(prototype);
    std::string token;

    while (std::getline(ss, token, ','))
    {
        parameters.push_back(token);
    }

//    for(int i = 0; i < parameters.size(); ++i)
//    {
//        std::cout << parameters[i] << " ";
//    }

//    for(int i = 0; i < args.size(); ++i)
//    {
//        std::cout << args[i].first << " ";
//    }

    int i = 0;
    if(args.size())
    {
        for(i = 0; i < args.size(); ++i)
        {
            if(parameters[i].find('=') == std::string::npos) //not a default argument
            {
                parameters[i] += " = " + std::to_string(args[i].first) + ';';
            }
            else
            {
                while(parameters[i].front() == ' ')
                {
                    parameters[i].erase(0,1);
                }
                while(parameters[i].back() != ' ')
                {
                    parameters[i].pop_back();
                }
                parameters[i] += std::to_string(args[i].first) + ';';
            }
        }
    }
    if(args.size() < parameters.size())
    {
        while(i != parameters.size())
        {
            while(parameters[i].front() == ' ')
            {
                parameters[i].erase(0,1);
            }
            parameters[i] += ';';
            ++i;
        }
    }

    for(int j = 0; j < parameters.size(); ++j)
    {
        //std::cout << parameters[i] << " " << std::endl;
//        if(j == parameters.size() - 1)
//        {
//            CB -> processString(this -> i, parameters[j]);
//            return;
//        }
//        std::cout << parameters[j] <<  " " << this -> i << std::endl;
        CB -> processString(this -> i, parameters[j]);
//        std::cout << "DFDSFD" << std::endl;
//        exit(0);
    }

}

std::tuple<int, int, int> Function::getInfo()
{
    //will be changed later
    return {std::get<1>(info[0]),std::get<2>(info[0]), std::get<3>(info[0])};
}

std::string Function::getReturnType()
{
    return returnType;
}

std::string Function::returnValue()
{
    //std::cout << "returned value is: |" << SC -> getValueByName("tmp_value").first <<"|" <<std::endl;
    return SC -> getValueByName("tmp_value").first;
    this -> ~Function();
}

Function::~Function()
{
        //std::cout <<'|' << name << '|' << std::endl;
}
