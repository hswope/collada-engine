#include "node.h"

Node::Node()
{
}

Node::~Node()
{
}

WorldObjectPtr Node::clone()
{
    NodePtr obj = NodePtr::create();
    obj->copy(*this);
    return obj;
}

void Node::copy(const Node &node)
{
    WorldObject::copy(node);
    transform = node.transform;
}

QMatrix4x4 Node::getTransform()
{
    return transform;
}

void Node::setTransform(QMatrix4x4 matrix)
{
    transform = matrix;
}

QMatrix4x4 Node::getAbsoluteTransform() const
{
    if (parent)
    {
        return transform * parent->transform;
    }
    return transform;
}


QVector3D Node::getPosition() const
{
    return QVector3D() * getAbsoluteTransform();
}

NodePtr Node::getParent()
{
    return parent;
}

void Node::setParent(NodePtr parent, NodePtr child)
{
    if (child->parent)
    {
        parent->nodes.remove(child->getId());
        child->parent.reset();
    }

    child->parent = parent;

    if (child->parent)
    {
        parent->nodes.insert(child->getId(),child);
    }
}

QMap<QString, NodePtr> &Node::getNodes()
{
    return nodes;
}
