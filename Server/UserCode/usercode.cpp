#include "usercode.h"

UserCode* UserCode::instance = nullptr;

UserCode::UserCode() : uiPtr(UIInterface::getUiInterface(MainWindow::getWindowInstance()))
{

}

UserCode* UserCode::getUserCode()
{
    if (!instance) {
        instance = new UserCode();
    }
    return instance;
}

void UserCode::enableIconColor(int i)
{
    uiPtr -> enableIconColor(i);
}

void UserCode::disableIconColor(int i)
{
    uiPtr -> disableIconColor(i);
}

void UserCode::addUserPage(const std::string& line, const int& i)
{
    uiPtr -> addUserPage(QString::fromStdString(line), i);
}
