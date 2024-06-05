#ifndef TYPECONTROLLER_H
#define TYPECONTROLLER_H

#include <sstream>


class TypeController {
public:
    explicit TypeController(const std::string type, const std::string name, const std::string codeLine);
    void createType();
    void createPointer();
    void createUniversalReference();
    void createArray();
    void resolveDeclaration();

    ~TypeController() = default;
private:
    std::string type;
    std::string name;
    std::string code;
};

#endif // TYPECONTROLLER_H
