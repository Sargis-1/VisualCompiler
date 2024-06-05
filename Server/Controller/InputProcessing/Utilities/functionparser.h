#ifndef FUNCTIONPARSER_H
#define FUNCTIONPARSER_H

class FunctionParser {
public:
    static std::string extractReturnType(const std::string& funcString);
    static std::string extractFunctionName(const std::string& funcString);
    static std::string extractArguments(const std::string& funcString);
private:
    FunctionParser();
};

#endif // FUNCTIONPARSER_H
