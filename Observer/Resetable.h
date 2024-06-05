#ifndef RESETABLE_H
#define RESETABLE_H

//Interface for resetable objects
//Each object which needs reseting after clicking reset, inherits from it
class Resetable {
public:
    virtual void update() = 0;
};

#endif // RESETABLE_H
