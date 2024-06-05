#include "controlengine.h"
#include "../../../Model/Include/Enums/returnType.h"
#include "../../ControlBlock/controlblock.h"
#include "../../../UserInterface/UIHeaders/uiinterface.h"

ControlEngine::ControlEngine(const std::string& path)
:
  inputFilePath_(path), compiler_(new Compiler()),
  preprocessor_(new Preprocessor()), formtter_(new StyleFormatter(path)),
  executor_(new Executor(path)), controlBlock_(ControlBlock::getControlBlock())
{
        this -> Formatt();
        this -> Run();
}

ControlEngine::~ControlEngine()
{
    if (compiler_) {
        delete compiler_;
        compiler_ = nullptr;
    }

    if (preprocessor_) {
        delete preprocessor_;
        preprocessor_ = nullptr;
    }

    if (formtter_) {
        delete formtter_;
        formtter_ = nullptr;
    }

    if (executor_) {
        delete executor_;
        executor_ = nullptr;
    }
}

void ControlEngine::Run()
{

    int i = 1; // CodeMap[0] == "";
    int result;
    while (i) {
        result = ExecuteLine(i);
        if (result == -1) {
            return;
        } else {
            i = result;
        }
    }
}

bool ControlEngine::Compile()
{
    std::string output = compiler_ -> Compile(inputFilePath_);
    ShowCompilationResult(output);
    return output.empty();
}

void ControlEngine::Process()
{
}

void ControlEngine::Formatt()
{
    if (formtter_) {
//        std::cout << 112 << std::endl;
        formtter_ -> run();
        delete formtter_;
        formtter_ = nullptr;
    } else {
        std::cout << "StyleFormatter it's wrong" << std::endl;
    }
}

int ControlEngine::ExecuteLine(int lineNumber, bool flag)
{

    returnType line = controlBlock_ -> ControllerHelper(lineNumber);
    switch (line) {
      case VARIABLE:
        return executor_ -> processVariableLine(lineNumber);
      case FUNCTION_DECLARATION:
        return executor_ -> processFuncDeclarationLine(lineNumber);
      case FUNCTION_DEFINITION:
        return executor_ -> processFunctionDefinitionLine(lineNumber, flag);
      case MAIN_FUNCTION:
        indexMain = lineNumber;
        afterMainFunction(executor_ -> processFunctionDefinitionLine(lineNumber, flag));
        executor_ -> showFunctionResults();
        return -1;
      default:
        throw std::runtime_error("Unknown Line Type");
    }
}

ControlEngine::operator int()
{
    return indexMain;
}

void ControlEngine::afterMainFunction(int index)
{
    int end = codeMap -> getCodeSize();
//static int i = 0;
//++i;
//std::cout << i << std::endl;
    for (; index < end - 1; ++index) {
        index = ExecuteLine(index, false);
        --index;
    }
}

void ControlEngine::ShowCompilationResult(const std::string &output)
{
    //std::cout << output << std::endl;
}
