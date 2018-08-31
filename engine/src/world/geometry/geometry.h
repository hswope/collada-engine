#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "../node.h"
#include <QSharedPointer>
#include <qopenglbuffer.h>
#include "../effect/material.h"

class QOpenGLVertexArrayObject;
class QOpenGLBuffer;
class Material;

class Geometry;
typedef QSharedPointer<Geometry> GeometryPtr;

class Geometry : public Node
{
public:
    Geometry();
    ~Geometry();

    virtual WorldObjectPtr clone();

    QSharedPointer<QOpenGLVertexArrayObject> &getVao();
    QSharedPointer<QOpenGLBuffer> &getVertexBuffer();
    QSharedPointer<QOpenGLBuffer> &getNormalBuffer();
    QSharedPointer<QOpenGLBuffer> &getUVBuffer();
    MaterialPtr getMaterial();
    void setMaterial(MaterialPtr material);

protected:
    QSharedPointer<QOpenGLVertexArrayObject> vao;
    QSharedPointer<QOpenGLBuffer> vertexBuffer;
    QSharedPointer<QOpenGLBuffer> normalBuffer;
    QSharedPointer<QOpenGLBuffer> uvBuffer;

    void copy(const Geometry &geometry);

private:

    MaterialPtr material;
};

#endif // GEOMETRY_H
