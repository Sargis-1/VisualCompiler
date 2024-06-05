#include "./controlblock.h"
#include "../../Model/Statements/Function/Function.h"
#include "../../Model/Statements/Conditions/IfCondition/ifCondition.h"
#include "../../Model/Statements/Conditions/While/While.h"

ControlBlock* ControlBlock::cbinstance = nullptr;

returnType ControlBlock::ControllerHelper(int codeLine)
{
    std::string currentString = codeMap -> getCode(codeLine);//read current processing line from CodeMap
    std::stringstream ss(currentString);
    std::string s;
    ss >> s;
    if (s == "") {
        return VARIABLE;  // will be changed
    }

    std::string token;
    std::stringstream iss(currentString);
    iss >> token;

    while (std::find(generalTypes.begin(), generalTypes.end(), token) != generalTypes.end()) {//tokeniz string while token is type or type specifier
        iss >> token;
    }

    //save token (which is probably is function or variable name)
    std::string tmp = token;
    if (iss >> token)  {
        if (token == "=") {
            return VARIABLE;
        }
    }

    if (token.find("main(") == std::string::npos) {
        if (isFunctionDefinition(currentString)) {
            return FUNCTION_DEFINITION;
        } else if (isFunctionDeclaration(tmp)) {
            return FUNCTION_DECLARATION;
        } else {
            return VARIABLE;
        }
    }

    return MAIN_FUNCTION;
}

std::string ControlBlock::processString(int& lineNumber, std::string code, bool arrowFlag)
{
//   timeDelay(1000);
   //std::cout << '|' << code << '|' <<std::endl;
    if (code == "") {
        if (codeMap -> getCode(lineNumber).find("main(") != std::string::npos && codeMap -> getCode(lineNumber).find(";") == std::string::npos) {
            //creat main function object
            return creatMainFunctionObject(lineNumber);
            }

        int findLineNumber = findInPreMain(lineNumber);//if statement is not function, findInPreMain will return -1
        if (findLineNumber != -1) {//if statement is function, findInPreMain will return last function statement
            lineNumber = findLineNumber;//line number will be corrected
            return "";
        }
    }

    std::string codeLine;
    if (code != "") {
        codeLine = code;
    } else {
        codeLine = codeMap -> getCode(lineNumber);//getting current executing code
    }

    if (codeLine == "") { //empty string
        return "";
    }

    if (arrowFlag) {
        cbUC -> enableIconColor(lineNumber);
    }
    std::string firstToken;
    std::istringstream iss(codeLine);
    iss >> firstToken;//get first token of the string
    if (firstToken == "{") {
        addnewScope();
        cbUC -> disableIconColor(lineNumber);
        return "";
    }

    if (firstToken == "}") {//if string is "}", the last scope should be deleted
        cbUC -> disableIconColor(lineNumber);
        removeLastScope();
        return "";
    }

    if (std::find(generalTypes.begin(), generalTypes.end(), firstToken) != generalTypes.end()) {//if first token is string
        std::string secondToken;
        iss >> secondToken;
        if (!isFunctionDeclaration(secondToken)) {//if statement is not function declaration (in function)
            resolveDeclaration(firstToken, secondToken, codeLine);//resolve variable declaration
        } else {
            resolveFuncDecl(secondToken, codeLine);//resolves the statement and shows the function info in UI
        }
    } else if (std::find(statements.begin(), statements.end(), firstToken) != statements.end()) {//if firstToken is control statment token
        return resolveStatment(firstToken, codeLine, lineNumber);
    } else {
        //take function name
        std::string funcName;
        if (codeLine.find('=') != std::string::npos) {
            resolveAssignment(firstToken, codeLine);
        } else if (firstToken.find('(') != std::string::npos) {//token is foo(5
            for (size_t i = 0; i < firstToken.size(); ++i) {
                if (firstToken[i] != '(') {
                    funcName += firstToken[i];
                } else {
                    break;
                }
            }
            //create function object
            return createFunctionObject(codeLine, lineNumber);
        } else {
            resolveUnaryOperators(firstToken, codeLine);//++k; !k;
        }
    }

    if (!arrowFlag) {
        timeDelay(300);
    } else {
        timeDelay();
    }
    if (arrowFlag) {
        cbUC -> disableIconColor(lineNumber);
    }
    return "";

}

std::string ControlBlock::processString(std::string code)
{
     //std::cout << "->>>    " << code << std::endl;
     //int y = foo();
     return createFunctionObject(code);
}

void ControlBlock::addnewScope(bool isFunction)
{
    //isFunction default value is false
    scope -> pushNewScope(isFunction);
}

void ControlBlock::removeLastScope()
{
    scope -> popLastScope();
}

void ControlBlock::removeLastFunctionScope()
{
    scope -> popFunctionScope();
}

//for handling start and stop
void ControlBlock::changeExecState(bool startClicked, bool stopClicked)
{
        this -> startClicked = startClicked;
        this -> stopClicked = stopClicked;

        if (stopClicked) {
            timer -> stop();
        }

        if (startClicked) {
            loop -> quit();
            QCoreApplication::processEvents(QEventLoop::AllEvents);
        }
}

void ControlBlock::setPreMain(std::vector<std::pair<int, int> > preMain)
{
    this -> preMain = preMain;
}

void ControlBlock::enableIconColor(int lineNumber)
{
    cbUC -> enableIconColor(lineNumber);
}

void ControlBlock::disableIconColor(int lineNumber)
{
    cbUC -> disableIconColor(lineNumber);
}

ControlBlock* ControlBlock::getControlBlock()
{
    if (!cbinstance) { //If no ControlBlock instance was created create one and return it
        cbinstance = new ControlBlock();
        provider -> subscribe(cbinstance);
    }
    return cbinstance;
}

ControlBlock::ControlBlock()
    :
      startClicked(false),
      stopClicked(false),
      timer (new QTimer()),
      loop (new QEventLoop()),
      cbRC(RamController::getRamController()),
      cbUC(UserCode::getUserCode()),
      scope(Scope::getScope())
{
    generalTypes = {"int", "char", "bool", "short", "float", "double", "long", "const", "unsigned", "signed" , "void"};
    statements = {"while", "for", "switch", "if"};
}

bool ControlBlock::isFunctionDeclaration(std::string& str)
{
    //str is a token of the string without type specifier
    //x;
    //x();
    //x{};
    //x(int);
    //x(int)
    //x(int
    //x(int());
    //etc

    int index = 0;
    while (index < str.size() && str[index] != '(' && str[index] != '{' && str[index] != ';') {
        ++index;
    }

    if (index < str.size() && str[index] == '{' || str[index] == ';') {//variable declaration
        return false;
    }

    ++index;

    if (index < str.size() && str[index] == ')') {//x();
        return true;
    }

    std::string isType;//check whether there is a type in the parentheses
    while (index < str.size() && str[index] >='a' && str[index] <= 'z') {
        isType += str[index];
        ++index;
    }

    if (isType.empty()) {//x(5);
        return false;
    }

    if(std::find(generalTypes.begin(), generalTypes.end(), isType) != generalTypes.end()) {
        //int x(bool b); //where str is "x(bool"
        if (str[str.size() - 1] != ';' || str[str.size() - 1] != ')') {
            return true;
        }
        //int x(int(double(char('a'))));
        //int x(int(double(char(val))));
        //int x(int(double(char(5))));
        //int x(int(double(char())));
        size_t lastIndex = str.size() - 2;
        while (str[lastIndex] == ')') {
            --lastIndex;
        }

        if (str[lastIndex] == '\'' || str[lastIndex] >= '0' && str[lastIndex] <= '9') {
            return false;//if last symbol is number or ascii symbol, statment is variable declaration, otherwise function declaration
        }
        return true;
    }
    //all other cases is variavle declaration
    return false;
}

bool ControlBlock::isFunctionDefinition(std::string& str)
{
    //clear last white spaces
    size_t endPos = str.find_last_not_of(" \t\n\r\f\v");
    str.erase(endPos + 1);

    //if statment doesn't end with ';' symbol, it means that it is function definition
    if (str[str.size() - 1] != ';') {
        return true;
    }

    return false;
}

void ControlBlock::resolveDeclaration(const std::string& type, const std::string& name, const std::string& declaration)
{
    TypeController(std::string(type), std::string(name), std::string(declaration));
}

std::string ControlBlock::resolveStatment(const std::string& token, const std::string& statement, int& lineNumber)
{
    timeDelay(1000);
    if (token == "if") {
        addnewScope();
        int startLine = lineNumber;
        lineNumber = ifCondition(statement, lineNumber);
        std::string currentCodeLine = codeMap -> getCode(lineNumber);
        std::string firstToken;
        std::istringstream iss(currentCodeLine);
        iss >> firstToken;
        if (firstToken == "return") {
            --lineNumber;
            cbUC -> disableIconColor(startLine);
            return "";
        } else if (firstToken == "break;" || firstToken == "continue;") {
            --lineNumber;
            cbUC -> disableIconColor(startLine);
            removeLastScope();
            return "";
        }
        cbUC -> enableIconColor(lineNumber);
        timeDelay(1500);
        removeLastScope();
        cbUC -> disableIconColor(lineNumber);
        cbUC -> disableIconColor(startLine);

    } else if (token == "while") {
        int startLine = lineNumber;
        While  while_object(statement, lineNumber);
        addnewScope();
        while (while_object.isRepeatable()) {
            while_object.execute();

            std::string currentCodeLine = codeMap -> getCode(while_object);
            std::string firstToken;
            std::istringstream iss(currentCodeLine);
            iss >> firstToken;
            if (firstToken == "return") {
                cbUC -> disableIconColor(startLine);
                lineNumber = while_object;
                return "";
            } else if (firstToken == "break;") {
                cbUC -> enableIconColor(while_object);
                timeDelay(1500);
                removeLastScope();
                cbUC -> disableIconColor(while_object);
                while_object.takeBreak();
                lineNumber = while_object;
                cbUC -> disableIconColor(startLine);
                return "";
            }

            cbUC -> enableIconColor(while_object);
            timeDelay(1500);
            removeLastScope();
            cbUC -> disableIconColor(while_object);
            addnewScope();
        }
        lineNumber = while_object;
        removeLastScope();
        std::string currentCodeLine = codeMap -> getCode(lineNumber);
        std::string firstToken;
        std::istringstream iss(currentCodeLine);
        iss >> firstToken;

        if (firstToken == "return") {
            cbUC -> disableIconColor(startLine);
            return "";
        }

        cbUC -> enableIconColor(lineNumber);
        timeDelay(1500);
        cbUC -> disableIconColor(lineNumber);
        cbUC -> disableIconColor(startLine);
    }
    return "";
    //other statements will be added later
}

void ControlBlock::resolveAssignment(const std::string& assign, const std::string& declaration)
{
    std::string type = scope -> getValueByName(assign).second;//returns variable type
    TypeController(std::string(type), std::string(assign), std::string(declaration));
}

void ControlBlock::resolveFuncDecl(const std::string& secondToken, const std::string& declaration)
{
//will show function declaration info in UI
}

void ControlBlock::resolveUnaryOperators(const std::string &expression, const std::string &declaration)
{
    std::string name;
    int i = 0;
    while (!std::isalpha(expression[i])) {//++x; !y;
        ++i;
    }

    while (expression[i] != ';' && expression[i] != ' ') {//++x; ++x + 5; ++x = 5;
        name += expression[i];
        ++i;
    }
    resolveAssignment(name, declaration);
}

//preMain contains all function (dec and dif) line numbers information which is avobe main
int ControlBlock::findInPreMain(int codeLine)
{
    for (auto each : preMain) {
        if (codeLine == each.first) {//if current line is function declaration or definition
            return each.second;//return count of lines which will be skipeed
        }
    }
    return -1;
}

std::string ControlBlock::createFunctionObject(const std::string& codeLine)
{
    std::vector<std::pair<double, std::string>> args;
    std::string call = codeLine;
    std::string call1 = Function::forAST(call);
    AST(call1,args);
    addnewScope(true);//creates function scope

    Function func(call,args);
    auto funcInfo = func.getInfo();//returns function prototype, start and end lineNumbers
    if (std::get<0>(funcInfo) != -1) {//if function has prototype
        cbUC -> enableIconColor(std::get<0>(funcInfo));//prototype
    }
    cbUC -> enableIconColor(std::get<1>(funcInfo));//start

    func.executeFunction();//calls function execution

    if(func.getReturnType() != "void") {
        std::string str = func.returnValue();
        removeLastFunctionScope();
        if (std::get<0>(funcInfo) != -1) {//if function has prototype
            cbUC -> disableIconColor(std::get<0>(funcInfo));//prototype
        }
        cbUC -> disableIconColor(std::get<1>(funcInfo));//start
        cbUC -> disableIconColor(std::get<2>(funcInfo));//end
        return str;
    }

    cbUC -> enableIconColor(std::get<2>(funcInfo));//if function has not return statment, enable function endLine
    removeLastFunctionScope();//remove all scopes of function
    //disable enabled arrows
    if (std::get<0>(funcInfo) != -1) {//if function has prototype
        cbUC -> disableIconColor(std::get<0>(funcInfo));//prototype
    }
    cbUC -> disableIconColor(std::get<1>(funcInfo));//start
    cbUC -> disableIconColor(std::get<2>(funcInfo));//end
    return "";
}

std::string ControlBlock::createFunctionObject(const std::string &codeLine, int &lineNumber)
{
//    std::cout << "codeLine1: " << codeLine << std::endl;

    int callLine = lineNumber;
    std::vector<std::pair<double, std::string>> args;
    std::string call = codeLine;
    std::string call1 = Function::forAST(call);
    AST(call1,args);
    addnewScope(true);//creates function scope

    Function func(call,args);
    auto funcInfo = func.getInfo();//returns function prototype, start and end lineNumbers
    if (std::get<0>(funcInfo) != -1) {//if function has prototype
        cbUC -> enableIconColor(std::get<0>(funcInfo));//prototype
    }
    cbUC -> enableIconColor(std::get<1>(funcInfo));//start

    if (!args.size()) {
        timeDelay(1500);
    }
    func.executeFunction();//calls function execution

    if(func.getReturnType() != "void") {
        std::string str = func.returnValue();
        removeLastFunctionScope();
        if (std::get<0>(funcInfo) != -1) {//if function has prototype
            cbUC -> disableIconColor(std::get<0>(funcInfo));//prototype
        }
        cbUC -> disableIconColor(std::get<1>(funcInfo));//start
        cbUC -> disableIconColor(std::get<2>(funcInfo));//end
        cbUC -> disableIconColor(callLine);//call pointing arrow
        return str;
    }

    cbUC -> enableIconColor(std::get<2>(funcInfo));//if function has not return statment, enable function endLine
    removeLastFunctionScope();//remove all scopes of function
    //disable enabled arrows
    if (std::get<0>(funcInfo) != -1) {//if function has prototype
        cbUC -> disableIconColor(std::get<0>(funcInfo));//prototype
    }
    cbUC -> disableIconColor(std::get<1>(funcInfo));//start
    cbUC -> disableIconColor(std::get<2>(funcInfo));//end
    cbUC -> disableIconColor(callLine);//call pointing arrow
    return "";
}

std::string ControlBlock::creatMainFunctionObject(int &lineNumber)
{
    cbUC -> enableIconColor(lineNumber);//enables main function startLine arrow
    std::vector<std::pair<double, std::string>> args;
    Function::forAST(codeMap -> getCode(lineNumber));
    addnewScope(true);//creates main function scope
    Function main_func("",args,"main");//creates main function object
    auto funcInfo = main_func.getInfo();//returns function prototype, start and end lineNumbers
    if (std::get<0>(funcInfo) != -1) {//if function has prototype
        cbUC -> enableIconColor(std::get<0>(funcInfo));//prototype
    }
    cbUC -> enableIconColor(std::get<1>(funcInfo));//start

    if (!args.size()) {
        timeDelay(1500);
    }
    main_func.executeFunction();//calls function execution

    //if main function has return type but has not return staement, will be incorrect
    if(main_func.getReturnType() != "void") {
        std::string str = main_func.returnValue();
        timeDelay(1000);
        removeLastFunctionScope();//delete main function scope
        timeDelay(500);
        removeLastScope();//delete global scope
        cbUC -> disableIconColor(lineNumber);
        addnewScope();//create global scope for next execution
        return str;
    }

    cbUC -> enableIconColor(std::get<2>(funcInfo));//if function has not return statment, enable function endLine
    removeLastFunctionScope();//remove all scopes of function
    //disable enabled arrowsfunc
    if (std::get<0>(funcInfo) != -1) {//if function has prototype
        cbUC -> disableIconColor(std::get<0>(funcInfo));//prototype
    }
    cbUC -> disableIconColor(std::get<1>(funcInfo));//start
    cbUC -> disableIconColor(std::get<2>(funcInfo));//end
    cbUC ->disableIconColor(lineNumber);//disables main function startLine arrow
    timeDelay(1000);
    removeLastScope();//delete global scope
    addnewScope();//create global scope for next execution
    return "";
}

void ControlBlock::timeDelay(int mSec)
{
    //for time delay
    loop = new QEventLoop();
    QObject::connect(timer, &QTimer::timeout, loop, &QEventLoop::quit);
    timer -> setInterval(mSec);
    timer -> start();
    loop -> exec();
    //delete loop;
}

void ControlBlock::update()
{//will be changed
    delete cbinstance;
    cbinstance = new ControlBlock();
}
