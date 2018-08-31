#include "scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
}

QMap<QString, CameraPtr> &Scene::getCameras()
{
    return cameras;
}

QMap<QString, LightPtr> &Scene::getLights()
{
    return lights;
}

QMap<QString, MeshPtr> &Scene::getMeshes()
{
    return meshes;
}

CameraPtr Scene::getCamera()
{
    QMapIterator<QString,CameraPtr> i(cameras);
    while (i.hasNext())
    {
        i.next();
        return i.value();
    }
    return CameraPtr();
}