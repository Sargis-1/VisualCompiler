#ifndef COMPILER_H
#define COMPILER_H

#include "../../../../UserInterface/UIHeaders/uiinterface.h"

#include <string>
#include <cstdlib>
#include <stdexcept>

class Compiler
{
public:
  Compiler();
  ~Compiler();

  std::string Compile(const std::string& filename, const std::string& additionalFlags = "");
  std::string Run();
  std::string CompileAndRun(const std::string& filename, const std::string& additionalFlags = "");

private:
  std::string readFromPipe(FILE* pipe);


  std::string FilePath_;
  FILE* compilePipe;
  FILE* compiledFilePipe;
};

#endif // COMPILER_H
