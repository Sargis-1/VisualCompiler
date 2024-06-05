#ifndef CODEMAP_H
#define CODEMAP_H

#include "../../../Observer/Provider.h"
//#include "../../../Server/UserCode/usercode.h"

class CodeMap {
public:
    CodeMap();//ctor
    void setCode(const std::string& codeLine);//sets in map line number and corresponding code text
    std::string getCode(unsigned int lineNumber);//returns the code text of the corresponding line

    void clearMap();//In case of when the code text changes
    int getCodeSize(); // return code size



private:
//    void initUICode();
    std::vector<std::string> code;
    //UserCode* ui;
};

extern CodeMap* codeMap;

#endif // CODEMAP_H
