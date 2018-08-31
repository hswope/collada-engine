#include "worldobject.h"

WorldObject::WorldObject()
{

}

WorldObject::~WorldObject()
{

}

WorldObjectPtr WorldObject::clone()
{
    WorldObjectPtr obj = WorldObjectPtr::create();
    obj->copy(*this);
    return obj;
}


void WorldObject::initializeGL()
{

}

void WorldObject::destroyGL()
{

}

void WorldObject::copy(const WorldObject &worldObject)
{
    name = worldObject.name;
}

QString WorldObject::getName()
{
    return name;
}

void WorldObject::setName(QString name)
{
    this->name = name;
}

QString WorldObject::getId()
{
    return id;
}

void WorldObject::setId(QString id)
{
    this->id = id;
}
