#ifndef PROVIDER_H
#define PROVIDER_H
#include "./Resetable.h"

//global pointer of Provider calls all Resetable objects update function
class Provider {
public:
    //All Resetable abjects need to subscribe to Provider
    void subscribe(Resetable* object);
    void resetAll();//Calls update function for each Resetable object of allResetables vector

private:
    std::vector<Resetable*> allResetables;
};

extern Provider* provider;
#endif // PROVIDER_H
