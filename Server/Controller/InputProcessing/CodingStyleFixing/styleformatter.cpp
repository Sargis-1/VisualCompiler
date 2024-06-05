#include "styleformatter.h"

StyleFormatter::StyleFormatter(const std::string& path)
{
    this -> path = path;
}

void StyleFormatter::run()
{
    if (path.empty()) {
        return;
    }
   // std::cout << path << std::endl;

    std::ifstream read;
    std::string str;

    read.open(path);
    if (!read.is_open()) {
        throw(std::runtime_error("File has not opened!"));
    }

    codeMap -> clearMap();

    while (!read.eof()) {
        std::getline(read, str);
        //std::cout << str << std::endl;
        codeMap -> setCode(str);
    }
    //codeMap -> setCode("END");//temporary string for checking the codeMap end

    if (read.is_open()) {
        read.close();
    }
}
