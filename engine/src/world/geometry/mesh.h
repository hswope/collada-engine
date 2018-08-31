#ifndef MESH_H
#define MESH_H

#include "geometry.h"

class Mesh;
typedef QSharedPointer<Mesh> MeshPtr;

class Mesh : public Geometry
{
public:
    Mesh();
    ~Mesh();

    virtual WorldObjectPtr clone();

    QVector<float> &getPositionData();
    QVector<float> &getNormalData();
    QVector<float> &getUVData();
    QVector<unsigned> &getPolyVertexCounts();
    QVector<unsigned> &getPolyVertexIndices();

    bool hasNormals() const;
    bool hasUVs() const;
    int getPolyCount() const;

    virtual void initializeGL();


protected:
    void copy(const Mesh &mesh);

private:
    QVector<float> positionData;
    QVector<float> normalData;
    QVector<float> uvData;
    QVector<unsigned> polyVertexCounts;
    QVector<unsigned> polyVertexIndices;

    void initializePositionData();
    void initializeNormalData();
    void initializeUVData();
};

#endif // MESH_H
