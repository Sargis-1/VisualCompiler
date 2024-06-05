#include "compiler.h"

Compiler::Compiler() : compilePipe(nullptr), compiledFilePipe(nullptr) {}

Compiler::~Compiler() {
    if (compilePipe) pclose(compilePipe);
    if (compiledFilePipe) pclose(compiledFilePipe);
}

std::string Compiler::readFromPipe(FILE* pipe) {
    std::string output;
    char buffer[128];
    while (!feof(pipe)) {
        if (fgets(buffer, 128, pipe) != nullptr) {
            output += buffer;
        }
    }
    return output;
}

std::string Compiler::Compile(const std::string& filename, const std::string& additionalFlags) {
    if (compilePipe || compiledFilePipe) {
        throw std::runtime_error("Another compilation or execution is in progress.");
    }

    std::string compileCommand = "g++ -o compiled_file " + filename + " " + additionalFlags + " 2>&1";
    compilePipe = popen(compileCommand.c_str(), "r");
    if (!compilePipe) {
        throw std::runtime_error("Failed to open pipe for compilation.");
    }

    return readFromPipe(compilePipe);
}

std::string Compiler::Run() {
    if (!compiledFilePipe) {
        throw std::runtime_error("No compiled file to run.");
    }

    return readFromPipe(compiledFilePipe);
}

std::string Compiler::CompileAndRun(const std::string& filename, const std::string& additionalFlags) {
    if (compilePipe || compiledFilePipe) {
        throw std::runtime_error("Another compilation or execution is in progress.");
    }

    std::string compileOutput = Compile(filename, additionalFlags);

    compiledFilePipe = popen("./compiled_file", "r");
    if (!compiledFilePipe) {
        throw std::runtime_error("Failed to execute compiled file.");
    }

    std::string runOutput = readFromPipe(compiledFilePipe);

    return "Compilation Output:\n" + compileOutput + "\n\nRun Output:\n" + runOutput;
}
