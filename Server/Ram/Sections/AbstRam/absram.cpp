#include "absram.h"

AbsRam::AbsRam(Segment segment, int currentAddress, int startAddress, bool enableAdressgGen) :
    ui(UIInterface::getUiInterface(MainWindow::getWindowInstance())), segmentId_(segment), currentAddress_(currentAddress), startAddress_(startAddress)
{
}

//Adds varibale with given values to according Ram Segment
void AbsRam::pushSlot(const std::string& value, const std::string& name, const std::string& size, const std::string& type)
{
    try {
        int variablesize = std::stoi(size); //convert given size string to integer
        const QString address = QString::fromStdString(generateAddress(variablesize)); //Generate address for given variable with given size
        ui->pushSlot(segmentId_, address , QString::fromStdString(value), QString::fromStdString(name), QString::fromStdString(size), QString::fromStdString(type));
    } catch (const std::exception& e) {
        qDebug() << e.what();
    }
}

//void AbsRam::enableIconColor(int i)
//{
//    ui -> enableIconColor(i);
//}
//void AbsRam::disableIconColor(int i)
//{
//    ui -> disableIconColor(i);
//}
//void AbsRam::addUserPage(const std::string& line, const int& i)
//{
//    ui -> addUserPage(QString::fromStdString(line), i);
//}

//Addes info about function to SymTab
void AbsRam::pushFunctionSlot(const std::string& returnType, const std::string& funcName, const std::string& args, std::tuple<int, int, int> info)
{
    ui -> pushFunctionSlot(segmentId_, QString::fromStdString(returnType), QString::fromStdString(funcName), QString::fromStdString(args), info);
}

//Set variable's value
void AbsRam::setSlotValue(int position, const std::string& value)
{
    try {
        ui -> setSlotValue(segmentId_, position, QString::fromStdString(value));
    } catch (const std::exception& e) {
        qDebug() << e.what();
    }
}

// arguments , prototype index,  implement start index, implement end index
std::vector<std::tuple<std::string, int, int, int>> AbsRam::getInfoFunctionByName(const std::string& functionName)
{
    return ui -> getInfoFunctionByName(segmentId_, QString::fromStdString(functionName));
//    return std::make_tuple(std::get<0>(info).toStdString(), std::get<1>(info), std::get<2>(info), std::get<3>(info));
}


 //Get variable value and type by name
std::pair<std::string, std::string> AbsRam::getValue(const std::string& name, int start, int end) const
{
    auto value = ui -> getValue(segmentId_, QString::fromStdString(name), start, end);//returns pair of strings
    std::pair<std::string, std::string> returnedValue;
    //convert QString to std::string
    returnedValue.first = value.first.toStdString();
    returnedValue.second = value.second.toStdString();
    return returnedValue;
}

 //Get variable address and type by name
std::pair<std::string, std::string> AbsRam::getAddress(const std::string& name, int start, int end) const
{
    auto value = ui -> getAddress(segmentId_, QString::fromStdString(name), start, end);//returns pair of strings
    std::pair<std::string, std::string> returnedValue;
    //convert QString to std::string
    returnedValue.first = value.first.toStdString();//address
    returnedValue.second = value.second.toStdString();//type
    return returnedValue;
}

//Get variable address and type by address
std::pair<std::string, std::string> AbsRam::getValueByAddress(const std::string& address) const
{
    try {
        auto value = ui -> getValueByAddress(segmentId_, QString::fromStdString(address));//returns pair of strings
        std::pair<std::string, std::string> returnedValue;
        //convert QString to std::string
        returnedValue.first = value.first.toStdString();//value
        returnedValue.second = value.second.toStdString();//type
        return returnedValue;
    } catch (const std::exception& e) {
        qDebug() << e.what();
    }
    return {"", ""};//if address not found, returns empty strings
}

//Resets the variable value
bool AbsRam::setValue(const std::string &name, const std::string& value, int start, int end)
{
    //check whether value was chenged or not
    bool isValueChanged = ui -> setValue(segmentId_, QString::fromStdString(name), QString::fromStdString(value), start, end);
    return isValueChanged;
}

//Resets the variable type
bool AbsRam::changeType(const std::string &name, const std::string &type, int start, int end)
{
    //check whether type was chenged or not
    bool isValueChanged = ui -> changeType(segmentId_, QString::fromStdString(name), QString::fromStdString(type), start, end);
    return isValueChanged;
}

std::size_t AbsRam::getSegmentSize() const //Added to be used in Scopes
{
    try {
        return ui->getSegmentSize(segmentId_);
    } catch (const std::exception& e) {
        qDebug() << e.what();
    }
    return std::numeric_limits<std::size_t>::max();
}

//Return index of name variable
std::size_t AbsRam::findSlotIndexbyName(const std::string& name)
{
    try {
        std::size_t index = ui -> findSlotIndexbyName(segmentId_, QString::fromStdString(name));
        return index;
    } catch (const std::exception& e) {
        qDebug() << e.what();
    }
    return std::numeric_limits<std::size_t>::max();
}

//Return index of variable by address
std::size_t AbsRam::findSlotIndexbyAddress(const std::string& address)
{
    try {
        std::size_t index = ui -> findSlotIndexbyAddress(segmentId_, QString::fromStdString(address));
        return index;
    } catch (const std::exception& e) {
        qDebug() << e.what();
    }
    return std::numeric_limits<std::size_t>::max();
}

//Erase some variabel named name
void AbsRam::erase(const std::string& name)
{
    try {
        ui -> erase(segmentId_, QString::fromStdString(name));
    } catch (const std::exception& e) {
        qDebug() << e.what();
    }
}

//Erase staring from index start
void AbsRam::eraseStartingFrom(int start)
{
    try {
        ui->eraseStartingFrom(segmentId_, start);
    } catch (const std::exception& e) {
        qDebug() << "Error from eraseStartingFrom() method" << e.what();
    }
}

//Erase SymTab
void AbsRam::eraseSymTab()
{
    try {
        ui->eraseSymTab(segmentId_);
    } catch (const std::exception& e) {
        qDebug() << "Error from eraseSymTab() method" << e.what();
    }
}

//Generate address for varibale being added
std::string AbsRam::generateAddress(int size)
{
    if (!addressGenenabled) { //if adress generation is not enabled, give segments first address as current addres
        //then set addressGenEnabled true, so later each address will be calculated using previous one
        std::stringstream ss;
        ss << std::hex << "0x"<< std::setw(8) << std::setfill('0') << startAddress_;
        addressGenenabled = true;
        return ss.str();
    }

    currentAddress_ += size;
    std::stringstream ss; //std::stringstream is a class that allows you to work with strings in a stream-like manner.
    //It acts as an in-memory output stream, meaning you can write data to it
    ss << std::hex << "0x"<< std::setw(8) << std::setfill('0') << currentAddress_;
    return ss.str(); //return the contents of the std::stringstream object as a std::string
    //   Adress distribution among all Ram Segments
    //     //0000 0000 - 5999 9994  - 35%
    //     //5999 9995 - B333 332A  - 35%
    //     //B333 332B - CCCC CCC3  - 10%
    //     //CCCC CCC4 - E666 665C  - 10%
    //     //E666 665D _ FFFF FFFF  - 10%
}

//For reseting addresses
void AbsRam::resetAddresses(int start)
{
    //when reset clicked addresses will be updated
    if (start == 0) {
        currentAddress_ = startAddress_;
        addressGenenabled = false;
        return;
    }
    currentAddress_ = ui -> getScopeStartAddress(segmentId_, start);
}
