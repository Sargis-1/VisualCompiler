#include "./TypeController.h"
#include "../../GeneralTypes/Types/Int/Int.h"
#include "../../GeneralTypes/Types/Char/Char.h"
#include "../../GeneralTypes/Types/Bool/Bool.h"
#include "../../GeneralTypes/Types/Double/Double.h"
#include "../../GeneralTypes/Types/Float/Float.h"
#include "../../GeneralTypes/Types/Short/Short.h"
#include "../../GeneralTypes/TypeArray/ShortArray/ShortArray.h"

TypeController::TypeController(const std::string type, const std::string name, const std::string codeLine)
    : type {type}, name {name}, code {codeLine}
{
    resolveDeclaration();
}

void TypeController::resolveDeclaration()
{
    if (name[0] == '*'){
        createPointer();
    } else if (name[0] == '&') {
        createUniversalReference();
    } else if (name.find('[') != std::string::npos) {
        createArray();
    } else {
        createType();
    }
}

void TypeController::createPointer()
{
    if (type == "int") {
//        IntPointer(std::string(code));
    } else if (type == "char") {
//        CharPointer(std::string(code));
    } else if (type == "bool") {
//        BoolPointer(std::string(code));
    } else if (type == "double") {
//        DoublePointer(std::string(code));
    } else if (type == "float") {
//        FloatPointer(std::string(code));
    } else if (type == "short") {
//        ShortPointer(std::string(code));
    }
}

void TypeController::createArray()
{
    if (type == "int") {
//        IntArray(std::string(code));
    } else if (type == "char") {
//        CharArray(std::string(code));
    } else if (type == "bool") {
//        BoolArray(std::string(code));
    } else if (type == "double") {
//        DoubleArray(std::string(code));
    } else if (type == "float") {
//        FloatArray(std::string(code));
    } else if (type == "short") {
        ShortArray(std::string(code));
    }
}

void TypeController::createUniversalReference()
{
    if (type == "int") {
//        IntUniversalReference(std::string(code));
    } else if (type == "char") {
//        CharUniversalReference(std::string(code));
    } else if (type == "bool") {
//        BoolUniversalReference(std::string(code));
    } else if (type == "double") {
//        DoubleUniversalReference(std::string(code));
    } else if (type == "float") {
//        FloatUniversalReference(std::string(code));
    } else if (type == "short") {
//        ShortUniversalReference(std::string(code));
    }
}


void TypeController::createType()
{
    if (type == "int") {
        Int(std::string(code));
    } else if (type == "char") {
        Char(std::string(code));
    } else if (type == "bool") {
        Bool(std::string(code));
    } else if (type == "double") {
        Double(std::string(code));
    } else if (type == "float") {
        Float(std::string(code));
    } else if (type == "short") {
        Short(std::string(code));
    }
}
