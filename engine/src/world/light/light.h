#ifndef LIGHT_H
#define LIGHT_H

#include "../node.h"

class Light;
typedef QSharedPointer<Light> LightPtr;

class Light : public Node
{
public:
    Light();
    ~Light();

    virtual WorldObjectPtr clone();

protected:
    void copy(const Light &light);

private:

};

#endif // LIGHT_H
