#ifndef BASETYPE_H
#define BASETYPE_H

#include "../../../Server/Ram/RamController/RamController.h"
#include "../../Include/Enums/segmentsenum.h"
#include "../../Include/AST/AST.h"
#include "../../../Observer/Provider.h"
#include "../../../Server/ControlBlock/controlblock.h"


class BaseType
{
protected:
    Segment segment;
    std::string name;
    std::string value;
    std::string size;
    std::string type;
    RamController* RC;
    Scope* SC;
    ControlBlock* CB;
    bool containsTypeInfo;

public:
    BaseType();
    std::vector<std::string> Tokenizing(std::string cur_line);
    virtual void ShowingObjectInUi(Segment segment, bool controlBssOrData = false);
    virtual void operator=(std::string unresolved_value) = 0;
    virtual ~BaseType();
};
#endif // BASETYPE_H
