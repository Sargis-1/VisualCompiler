#include "functionparser.h"
#include <regex>

std::string FunctionParser::extractReturnType(const std::string& funcString)
{
    std::regex pattern("\\s*([^\\s]+(?:\\s+[^\\s]+)*)\\s+\\w+\\(.*\\)\\s*;\\s*(?:\\/\\/.*|\\/\\*(?:[^*]|(?:\\*+[^*\\/]))*\\*+\\/\\s*)?");
    std::smatch match;
    if (std::regex_search(funcString, match, pattern)) {
       return match[1];
    } else {
       return ""; // Return an empty string if no match is found
    }
}

std::string FunctionParser::extractFunctionName(const std::string& funcString)
{
    std::regex pattern("\\s*(?:[^\\s<]+|\\s*\\w+\\s*<[^<>]+>\\s*)\\s+(\\w+)\\s*\\(.*\\)\\s*;\\s*(?:\\/\\/.*\\n|\\/\\*(?:.|\\n)*?\\*\\/)?");
    std::smatch match;
    if (std::regex_search(funcString, match, pattern)) {
       return match[1];
    } else {
       return ""; // Return an empty string if no match is found
    }
}

std::string FunctionParser::extractArguments(const std::string& funcString)
{
    std::regex pattern("\\(([^;]*)\\)");
    std::smatch match;
    if (std::regex_search(funcString, match, pattern)) {
       return match[1];
    } else {
       return ""; // Return an empty string if no match is found
    }
}

FunctionParser::FunctionParser()
{

}
