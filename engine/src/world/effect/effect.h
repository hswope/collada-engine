#ifndef EFFECT_H
#define EFFECT_H

#include "../worldobject.h"

class Effect;
typedef QSharedPointer<Effect> EffectPtr;

class Effect : public WorldObject
{
public:
    Effect();
    ~Effect();

    virtual WorldObjectPtr clone();

protected:
    void copy(const Effect &effect);

private:
};

#endif // EFFECT_H
