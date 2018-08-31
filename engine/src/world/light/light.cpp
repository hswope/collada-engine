#include "light.h"

Light::Light()
{
}

Light::~Light()
{
}

WorldObjectPtr Light::clone()
{
    LightPtr obj = LightPtr::create();
    obj->copy(*this);
    return obj;
}

void Light::copy(const Light &light)
{
    Node::copy(light);
}
