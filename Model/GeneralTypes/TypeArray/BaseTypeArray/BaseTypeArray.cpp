#include "BaseTypeArray.h"

void BaseTypeArray::ShowInUI(int ArrSize)
{
    if (SC -> getScopeIndex() == 0) {
       value = "0";
    } else {
       value = "Garbage";
    }
    std::string tmp = name;
    for (int i = 0; i < ArrSize; ++i) {
        name = tmp + "[" + std::to_string(i) + "]";
        ShowingObjectInUi(segment);
    }
}

void BaseTypeArray::ShowInUI(int ArrSize, std::vector<std::string> vec) {
    bool flag = true;
    if (!vec.size()) {
        flag = false;
    }
    while (ArrSize > vec.size()) {
        vec.push_back("0");
    }
    std::string tmp = name;
    for (int i = 0; i < ArrSize; ++i) {
        value = vec[i];
        name = tmp + "[" + std::to_string(i) + "]";
        ShowingObjectInUi(segment, flag);
    }
}

BaseTypeArray::~BaseTypeArray()
{

}
