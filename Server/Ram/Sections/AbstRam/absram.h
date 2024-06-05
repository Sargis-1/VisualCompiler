#ifndef ABSRAM_H
#define ABSRAM_H
#include "../../../../UserInterface/UIHeaders/uiinterface.h"

//Base class for all Ram Segment classes in Server
//Used to implement dynamic polymorphysm
//AbsRam* pointers can be bind to all types of derived objects, Stack, Heap, Bss, Data, ReadOnly, SymTab derive from this class publicly
class AbsRam {
public:
    AbsRam(Segment segment, int currentAddress, int startAddress, bool enableAdressgGen = 0);
    virtual ~AbsRam() = default;

    void pushSlot(const std::string& value, const std::string& name, const std::string& size, const std::string& type); //Adds varibale with given values to according Ram Segment
    void pushFunctionSlot(const std::string& returnType, const std::string& funcName, const std::string& args, std::tuple<int, int, int> info);
    void setSlotValue(int position, const std::string& value); //Set variable's value

    std::pair<std::string, std::string> getValue(const std::string&  name, int start, int end) const; //Get variable value and type by name
    std::pair<std::string, std::string> getAddress(const std::string&  name, int start, int end) const; //Get variable address and type by name
    std::pair<std::string, std::string> getValueByAddress(const std::string& name) const; //Get variable address and type by address

   std::vector<std::tuple<std::string, int, int, int>> getInfoFunctionByName(const std::string& functionName);

    bool setValue(const std::string&  name, const std::string&  value, int start, int end);//Resets the variable value
    bool changeType(const std::string&  name, const std::string& type, int start, int end);//Resets the variable type

    std::size_t getSegmentSize() const; //Get Segment size
    std::size_t findSlotIndexbyName(const std::string& name); //Return index of name variable
    std::size_t findSlotIndexbyAddress(const std::string& address); //Return index of variable by address

    void erase(const std::string& name); //Erase some variabel named name
    void eraseStartingFrom(int start); //Erase staring from index start
    void eraseSymTab();//Erase SymTab

    virtual std::string generateAddress(int size); //Generate address for varibale being added
    void resetAddresses(int start); //For reseting addresses

//    void enableIconColor(int);
//    void disableIconColor(int);
//    void addUserPage(const std::string&, const int& i);

protected:
    Segment segmentId_; //Enum to differ between Segments
    unsigned int currentAddress_; //last generated addres for this segment
    const unsigned int startAddress_; //starting address for this segment
    bool addressGenenabled; //used to solve the issue of using very first address, for ex. 0x0000 0000
    UIInterface* ui; //Pointer to ui interface to have access to its methods
};

#endif // ABSRAM_H
