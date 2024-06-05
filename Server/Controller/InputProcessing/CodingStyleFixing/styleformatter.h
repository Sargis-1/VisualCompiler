#ifndef STYLEFORMATTER_H
#define STYLEFORMATTER_H
#include "../../../../Model/Include/CodeMap/CodeMap.h"

class StyleFormatter {
public:
    StyleFormatter(const std::string& path);
    void run();

private:
    std::string path;
};

#endif // STYLEFORMATTER_H
