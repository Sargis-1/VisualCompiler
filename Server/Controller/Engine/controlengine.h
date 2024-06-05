#ifndef CONTROLENGINE_H
#define CONTROLENGINE_H

#include "../InputProcessing/Compiling/compiler.h"
#include "../InputProcessing/Preprocessing/preprocessor.h"
#include "../InputProcessing/CodingStyleFixing/styleformatter.h"
#include "../InputProcessing/Executing/executor.h"
#include "../../ControlBlock/controlblock.h"
#include "../../../Model/Include/CodeMap/CodeMap.h"

class ControlEngine {
public:
    ControlEngine(const std::string& path);
    ~ControlEngine();
    void Run();

    bool Compile();
    void Process();
    void Formatt();
    int ExecuteLine(int lineNumer, bool flag = true);

    operator int();

private:
    void ShowCompilationResult(const std::string& output);
    void afterMainFunction(int index);

    int indexMain;
    std::string inputCode_;
    std::string inputFilePath_;

    ControlBlock* controlBlock_;
    Compiler* compiler_;
    Preprocessor* preprocessor_;
    StyleFormatter* formtter_;
    Executor* executor_;
};

#endif // CONTROLENGINE_H
