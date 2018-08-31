#include "geometry.h"
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include "../effect/material.h"

Geometry::Geometry()
{
    vao = QSharedPointer<QOpenGLVertexArrayObject>(new QOpenGLVertexArrayObject());
    vertexBuffer = QSharedPointer<QOpenGLBuffer>(new QOpenGLBuffer());
    normalBuffer = QSharedPointer<QOpenGLBuffer>(new QOpenGLBuffer());
    uvBuffer = QSharedPointer<QOpenGLBuffer>(new QOpenGLBuffer());
}

Geometry::~Geometry()
{
}

WorldObjectPtr Geometry::clone()
{
    GeometryPtr obj = GeometryPtr::create();
    obj->copy(*this);
    return obj;
}

void Geometry::copy(const Geometry &geometry)
{
    Node::copy(geometry);

    this->vao = geometry.vao;
    this->vertexBuffer = geometry.vertexBuffer;
    this->normalBuffer = geometry.normalBuffer;
    this->uvBuffer = geometry.uvBuffer;
}

QSharedPointer<QOpenGLVertexArrayObject> &Geometry::getVao()
{
    return vao;
}

QSharedPointer<QOpenGLBuffer> &Geometry::getVertexBuffer()
{
    return vertexBuffer;
}


QSharedPointer<QOpenGLBuffer> &Geometry::getNormalBuffer()
{
    return normalBuffer;
}


QSharedPointer<QOpenGLBuffer> &Geometry::getUVBuffer()
{
    return uvBuffer;
}

MaterialPtr Geometry::getMaterial()
{
    return material;
}

void Geometry::setMaterial(MaterialPtr material)
{
    this->material = material;
}
