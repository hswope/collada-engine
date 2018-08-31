#ifndef COLLADAIMPORTER_H
#define COLLADAIMPORTER_H

#include <QString>
#include <QDomElement>
#include <QDir>
#include "worldobject.h"
#include "world.h"
#include "geometry/mesh.h"
#include "node.h"
#include "light/pointlight.h"

class ColladaImporter
{
public:
    ColladaImporter();
    ~ColladaImporter();

    WorldPtr importWorld(QString path);

private:
    WorldPtr world;
    QDomElement root;
    QDir dir;

    QString getIdFromUrl(QString url);
    QMatrix4x4 elementToMatrix4x4(QDomElement element);
    void elementToFloatVector(QDomElement element, QVector<float> &vector);
    void elementToVector3DVector(QDomElement element, QVector<QVector3D> &vector);
    void elementToUIntVector(QDomElement element, QVector<unsigned> &vector);
    QDomElement getChildWithId(QDomElement parent, QString id);
    void getChildElementsByTagName(QDomElement parent, QString tagName, QList<QDomElement> &list);
    WorldObjectPtr getWorldObject(QDomElement parent);
    Color elementToColor(QDomElement element);
    void makeYUp(QVector<float> &vector);
    QMatrix4x4 makeYUp(QMatrix4x4 matrix);

    void setGeoemetryNodeProperties(GeometryPtr geometry, QDomElement element);

    CameraPtr createCamera(QDomElement element);
    PointLightPtr createPointLight(QDomElement element);
    LightPtr createLight(QDomElement element);
    ImagePtr createImage(QDomElement element);
    EffectPtr createEffect(QDomElement element);
    MaterialPtr createMaterial(QDomElement element);
    MeshPtr createMesh(QDomElement element);
    GeometryPtr createGeometry(QDomElement element);
    ControllerPtr createController(QDomElement element);
    ScenePtr createScene(QDomElement element);
    NodePtr createNode(QDomElement element);

    void loadCameras();
    void loadLights();
    void loadImages();
    void loadEffects();
    void loadMaterials();
    void loadGeometries();
    void loadControllers();
    void loadScenes();

};

#endif // COLLADAIMPORTER_H
