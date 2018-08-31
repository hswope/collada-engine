#ifndef WORLD_H
#define WORLD_H

#include <QObject>
#include <QMap>

#include "camera.h"
#include "light/light.h"
#include "effect/image.h"
#include "effect/effect.h"
#include "effect/material.h"
#include "geometry/geometry.h"
#include "controller.h"
#include "scene.h"

class World;
typedef QSharedPointer<World> WorldPtr;

class World
{
public:
    World();
    ~World();

    void initializeGL();
    void destroyGL();

    QMap<QString, CameraPtr> &getCameras();
    QMap<QString, LightPtr> &getLights();
    QMap<QString, ImagePtr> &getImages();
    QMap<QString, EffectPtr> &getEffects();
    QMap<QString, MaterialPtr> &getMaterials();
    QMap<QString, GeometryPtr> &getGeometries();
    QMap<QString, ControllerPtr> &getControllers();
    QMap<QString, ScenePtr> &getScenes();

private:
    QMap<QString, CameraPtr> cameras;
    QMap<QString,LightPtr> lights;
    QMap<QString,ImagePtr> images;
    QMap<QString,EffectPtr> effects;
    QMap<QString,MaterialPtr> materials;
    QMap<QString,GeometryPtr> geometries;
    QMap<QString,ControllerPtr> controllers;
    QMap<QString,ScenePtr> scenes;
};

#endif // WORLD_H
