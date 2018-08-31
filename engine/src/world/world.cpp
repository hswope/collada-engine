#include "world.h"

World::World()
{
}

World::~World()
{
}

void World::initializeGL()
{
    foreach(CameraPtr ptr, cameras)
    {
        ptr->initializeGL();
    }

    foreach(LightPtr ptr, lights)
    {
        ptr->initializeGL();
    }

    foreach(ImagePtr ptr, images)
    {
        ptr->initializeGL();
    }

    foreach(EffectPtr ptr, effects)
    {
        ptr->initializeGL();
    }

    foreach(MaterialPtr ptr, materials)
    {
        ptr->initializeGL();
    }

    foreach(GeometryPtr ptr, geometries)
    {
        ptr->initializeGL();
    }

    foreach(ControllerPtr ptr, controllers)
    {
        ptr->initializeGL();
    }

    foreach(ScenePtr ptr, scenes)
    {
        ptr->initializeGL();
    }
}

void World::destroyGL()
{
    foreach(CameraPtr ptr, cameras)
    {
        ptr->destroyGL();
    }
    cameras.clear();

    foreach(LightPtr ptr, lights)
    {
        ptr->destroyGL();
    }
    lights.clear();

    foreach(ImagePtr ptr, images)
    {
        ptr->destroyGL();
    }
    images.clear();

    foreach(EffectPtr ptr, effects)
    {
        ptr->destroyGL();
    }
    effects.clear();

    foreach(MaterialPtr ptr, materials)
    {
        ptr->destroyGL();
    }
    materials.clear();

    foreach(GeometryPtr ptr, geometries)
    {
        ptr->destroyGL();
    }
    geometries.clear();

    foreach(ControllerPtr ptr, controllers)
    {
        ptr->destroyGL();
    }
    controllers.clear();

    foreach(ScenePtr ptr, scenes)
    {
        ptr->destroyGL();
    }
    scenes.clear();
}

QMap<QString, CameraPtr> &World::getCameras()
{
    return cameras;
}

QMap<QString, LightPtr> &World::getLights()
{
    return lights;
}

QMap<QString, ImagePtr> &World::getImages()
{
    return images;
}

QMap<QString, EffectPtr> &World::getEffects()
{
    return effects;
}

QMap<QString, MaterialPtr> &World::getMaterials()
{
    return materials;
}

QMap<QString, GeometryPtr> &World::getGeometries()
{
    return geometries;
}

QMap<QString, ControllerPtr> &World::getControllers()
{
    return controllers;
}

QMap<QString, ScenePtr> &World::getScenes()
{
    return scenes;
}
