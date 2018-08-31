#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "worldobject.h"

class Controller;
typedef QSharedPointer<Controller> ControllerPtr;

class Controller : public WorldObject
{
public:
    Controller();
    ~Controller();

    virtual WorldObjectPtr clone();

protected:
    void copy(const Controller &controller);
    
private:

};

#endif // CONTROLLER_H
