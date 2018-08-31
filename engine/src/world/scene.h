#ifndef SCENE_H
#define SCENE_H

#include "worldobject.h"
#include <QMap>
#include "camera.h"
#include "light/light.h"
#include "geometry/mesh.h"

class Scene;
typedef QSharedPointer<Scene> ScenePtr;

class Scene : public WorldObject
{
public:
    Scene();
    ~Scene();

    QMap<QString,CameraPtr> &getCameras();
    QMap<QString,LightPtr> &getLights();
    QMap<QString,MeshPtr> &getMeshes();

    CameraPtr getCamera();

protected:
    virtual WorldObjectPtr clone(){return ScenePtr();};

private:
    QMap<QString,CameraPtr> cameras;
    QMap<QString,LightPtr> lights;
    QMap<QString,MeshPtr> meshes;
};

#endif // SCENE_H
