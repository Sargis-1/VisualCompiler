#include "./Provider.h"

void Provider::subscribe(Resetable* object)
{
    allResetables.push_back(object);
}

void Provider::resetAll()
{
    //Calls update for each Resetable object of allResetables vector
    for (Resetable*& current : allResetables) {
        current -> update();
    }
}
