#include "effect.h"

Effect::Effect()
{
}

Effect::~Effect()
{
}

WorldObjectPtr Effect::clone()
{
    EffectPtr obj = EffectPtr::create();
    obj->copy(*this);
    return obj;
}

void Effect::copy(const Effect &effect)
{
    WorldObject::copy(effect);
}
