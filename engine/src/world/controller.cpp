#include "controller.h"

Controller::Controller()
{
}

Controller::~Controller()
{
}

WorldObjectPtr Controller::clone()
{
    ControllerPtr obj = ControllerPtr::create();
    obj->copy(*this);
    return obj;
}

void Controller::copy(const Controller &controller)
{
    WorldObject::copy(controller);
}
