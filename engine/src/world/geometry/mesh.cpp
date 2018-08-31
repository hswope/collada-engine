#include "mesh.h"
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>

Mesh::Mesh()
{
}

Mesh::~Mesh()
{
}

WorldObjectPtr Mesh::clone()
{
    MeshPtr obj = MeshPtr::create();
    obj->copy(*this);
    return obj;
}

void Mesh::copy(const Mesh &mesh)
{
    Geometry::copy(mesh);
    positionData = mesh.positionData;
    normalData = mesh.normalData;
    polyVertexCounts = mesh.polyVertexCounts;
    polyVertexIndices = mesh.polyVertexIndices;
}

QVector<float> &Mesh::getPositionData()
{
    return positionData;
}

QVector<float> &Mesh::getNormalData()
{
    return normalData;
}


QVector<float> &Mesh::getUVData()
{
    return uvData;
}

QVector<unsigned> &Mesh::getPolyVertexCounts()
{
    return polyVertexCounts;
}

QVector<unsigned> &Mesh::getPolyVertexIndices()
{
    return polyVertexIndices;
}

bool Mesh::hasNormals() const
{
    return normalData.count() > 0;
}

bool Mesh::hasUVs() const
{
    return uvData.count() > 0;
}

int Mesh::getPolyCount() const
{
    return polyVertexCounts.count();
}

void Mesh::initializePositionData()
{
    vertexBuffer->create();
    vertexBuffer->bind();
    vertexBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    vertexBuffer->allocate(getPolyCount() * 3 * 3 * sizeof(float));

    int loop = 0;
    int lend = polyVertexIndices.count();
    int offset = 0;
    int loopInc = 1;
    if (hasNormals()) loopInc++;
    if (hasUVs()) loopInc++;
    for (loop = 0; loop < lend; loop+=loopInc)
    {
        vertexBuffer->write(offset,&positionData.at(polyVertexIndices.at(loop)*3),3*sizeof(float));
        offset += 3 * sizeof(float);
    }

    vertexBuffer->release();
}

void Mesh::initializeNormalData()
{
    normalBuffer->create();
    normalBuffer->bind();
    normalBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    normalBuffer->allocate(getPolyCount() * 3 * 3 * sizeof(float));

    int loop = 0;
    int lend = polyVertexIndices.count();
    int offset = 0;
    int loopInc = 1;
    if (hasNormals()) loopInc++;
    if (hasUVs()) loopInc++;
    for (loop = 1; loop < lend; loop+=loopInc) // polyVertexIndices are interleaved should start at 1
    {
        normalBuffer->write(offset,&normalData.at(polyVertexIndices.at(loop)*3),3*sizeof(float));
        offset += 3 * sizeof(float);
    }

    normalBuffer->release();
}

void Mesh::initializeUVData()
{
    uvBuffer->create();
    uvBuffer->bind();
    uvBuffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    uvBuffer->allocate(getPolyCount() * 3 * 2 * sizeof(float));

    int loop = 0;
    int lend = polyVertexIndices.count();
    int offset = 0;
    int loopInc = 1;
    if (hasNormals()) loopInc++;
    if (hasUVs()) loopInc++;
    for (loop = 2; loop < lend; loop+=loopInc) // polyVertexIndices are interleaved should start at 2
    {
        uvBuffer->write(offset,&uvData.at(polyVertexIndices.at(loop)*2),2*sizeof(float));
        offset += 2 * sizeof(float);
    }

    uvBuffer->release();
}

void Mesh::initializeGL()
{
    vao->create();
    vao->bind();

    initializePositionData();
    if (hasNormals())
        initializeNormalData();
    if (hasUVs())
        initializeUVData();

    vao->release();
}
