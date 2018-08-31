#ifndef WORLDOBJECT_H
#define WORLDOBJECT_H

#include <QString>
#include <QSharedPointer>
#include "effect/color.h"

class WorldObject;
typedef QSharedPointer<WorldObject> WorldObjectPtr;

class WorldObject
{
public:
    WorldObject();
    ~WorldObject();

    virtual WorldObjectPtr clone();
    virtual void initializeGL();
    virtual void destroyGL();

    QString getName();
    void setName(QString name);

    QString getId();
    void setId(QString id);

protected:
    void copy(const WorldObject &worldObject);

private:
    QString name;
    QString id;
};

#endif // WORLDOBJECT_H
