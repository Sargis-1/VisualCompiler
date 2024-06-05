#ifndef USERCODE_H
#define USERCODE_H

#include "../../UserInterface/UIHeaders/uiinterface.h"

class UserCode
{
public:
    static UserCode* getUserCode();
    void enableIconColor(int);
    void disableIconColor(int);
    void addUserPage(const std::string&, const int&);
private:
    UserCode();
    static UserCode* instance;
    UIInterface* uiPtr;
};

#endif // USERCODE_H
