#ifndef NODE_H
#define NODE_H

#include "worldobject.h"
#include <QMatrix4x4>

class Node;
typedef QSharedPointer<Node> NodePtr;

class Node : public WorldObject
{
public:
    Node();
    ~Node();

    virtual WorldObjectPtr clone();

    QMatrix4x4 getTransform();
    void setTransform(QMatrix4x4 matrix);
    QMatrix4x4 getAbsoluteTransform() const;
    QVector3D getPosition() const;

    NodePtr getParent();
    static void setParent(NodePtr parent, NodePtr child); // this is static to maintain proper reference counting through QSharedPointer

    QMap<QString,NodePtr> &getNodes();

protected:
    void copy(const Node &node);

private:
    QMatrix4x4 transform;
    NodePtr parent;
    QMap<QString,NodePtr> nodes;
};

#endif // NODE_H
