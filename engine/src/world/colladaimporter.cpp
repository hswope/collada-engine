#include "colladaimporter.h"
#include "node.h"

#include <QFile>
#include <QDomDocument>
#include <QDir>
#include <iostream>
using namespace std;

#include "world.h"

ColladaImporter::ColladaImporter()
{
}

ColladaImporter::~ColladaImporter()
{

}

void ColladaImporter::makeYUp(QVector<float> &vector)
{
    for(int loop = 0; loop < vector.count(); loop+=3)
    {
        float x = vector[loop];
        float y = vector[loop+1];
        float z = vector[loop+2];
        vector[loop+1] = z;
        vector[loop+2] = -y;
    }
}


QMatrix4x4 ColladaImporter::makeYUp(QMatrix4x4 matrix)
{
    QMatrix4x4 zUp = QMatrix4x4(1,0,0,0,0,0,-1,0,0,1,0,0,0,0,0,1);
    QMatrix4x4 yUp = QMatrix4x4(1,0,0,0,0,0,1,0,0,-1,0,0,0,0,0,1);

    return zUp * matrix;
    //return matrix;
}

QString ColladaImporter::getIdFromUrl(QString url)
{
    return url.mid(1);
}

QMatrix4x4 ColladaImporter::elementToMatrix4x4(QDomElement element)
{
    QString strValues = element.text();
    QStringList valueList = strValues.split(" ");
    Q_ASSERT(valueList.count() == 16);
    QMatrix4x4 matrix;
    for (int loop = 0; loop < valueList.count(); loop++)
    {
        matrix.data()[loop] = valueList[loop].toFloat();
    }
    return makeYUp(matrix);
}

void ColladaImporter::elementToFloatVector(QDomElement element, QVector<float> &vector)
{
    QString strValues = element.text();
    QStringList valueList = strValues.split(" ");
    for (int loop = 0; loop < valueList.count(); loop++)
    {
        vector.append(valueList[loop].toFloat());
    }
    makeYUp(vector);
}


void ColladaImporter::elementToVector3DVector(QDomElement element, QVector<QVector3D> &vector)
{
    QString strValues = element.text();
    QStringList valueList = strValues.split(" ");
    for (int loop=0; loop < valueList.count(); loop+=3)
    {
        vector.append(QVector3D(valueList[loop].toFloat(),valueList[loop+1].toFloat(),valueList[loop+2].toFloat()));
    }
}

void ColladaImporter::elementToUIntVector(QDomElement element, QVector<unsigned> &vector)
{
    QString strValues = element.text();
    QStringList valueList = strValues.split(" ");
    for (int loop = 0; loop < valueList.count(); loop++)
    {
        if (!valueList[loop].isEmpty())
        {
            vector.append(valueList[loop].toUInt());
        }
    }
}

Color ColladaImporter::elementToColor(QDomElement element)
{
    if (element.tagName() == "color")
    {
        QString strValues = element.text();
        QStringList list = strValues.split(" ");

        if (list.count() == 4)
            return QColor::fromRgbF(list[0].toFloat(), list[1].toFloat(), list[2].toFloat(), list[3].toFloat());
        else if (list.count() == 3)
            return QColor::fromRgbF(list[0].toFloat(), list[1].toFloat(), list[2].toFloat());
        else
            Q_ASSERT(false);
    }
    if (element.tagName() == "texture")
    {
        return Color(element.attribute("texture"));
    }

    return QColor();
}

QDomElement ColladaImporter::getChildWithId(QDomElement parent, QString id)
{
    QDomNodeList children = parent.childNodes();
    for (int loop = 0; loop < children.count(); loop++)
    {
        QDomNode childNode = children.at(loop);
        if (!childNode.isElement()) continue;
        QDomElement child = childNode.toElement();
        if (child.attribute("id") == id)
        {
            return child;
        }
    }
    return QDomElement();
}

void ColladaImporter::getChildElementsByTagName(QDomElement parent, QString tagName, QList<QDomElement> &list)
{
    QDomNodeList children = parent.childNodes();
    for (int loop = 0; loop < children.count(); loop++)
    {
        QDomNode childNode = children.at(loop);
        if (!childNode.isElement()) continue;
        QDomElement child = childNode.toElement();
        if (child.tagName() == tagName)
        {
            list.append(child);
        }
    }
}

WorldObjectPtr ColladaImporter::getWorldObject(QDomElement parent)
{
    QDomNodeList children = parent.childNodes();
    for (int loop = 0; loop < children.count(); loop++)
    {
        QDomNode childNode = children.at(loop);
        if (!childNode.isElement()) continue;
        QDomElement child = childNode.toElement();
        if (child.tagName().startsWith("instance_"))
        {
            if (child.tagName() == "instance_camera")
            {
                return world->getCameras().value(getIdFromUrl(child.attribute("url")));
            }
            if (child.tagName() == "instance_light")
            {
                return world->getLights().value(getIdFromUrl(child.attribute("url")));
            }
            if (child.tagName() == "instance_image")
            {
                return world->getImages().value(getIdFromUrl(child.attribute("url")));
            }
            if (child.tagName() == "instance_effect")
            {
                return world->getEffects().value(getIdFromUrl(child.attribute("url")));
            }
            if (child.tagName() == "instance_material")
            {
                return world->getMaterials().value(getIdFromUrl(child.attribute("url")));
            }
            if (child.tagName() == "instance_geometry")
            {
                return world->getGeometries().value(getIdFromUrl(child.attribute("url")));
            }
            if (child.tagName() == "instance_controller")
            {
                return world->getControllers().value(getIdFromUrl(child.attribute("url")));
            }
            if (child.tagName() == "instance_visual_scene")
            {
                return world->getScenes().value(getIdFromUrl(child.attribute("url")));
            }
        }
    }
    return WorldObjectPtr();
}

void ColladaImporter::setGeoemetryNodeProperties(GeometryPtr geometry, QDomElement element)
{
    QDomElement bindMaterial = element.firstChildElement("bind_material");
    if (!bindMaterial.isNull())
    {
        QString id = getIdFromUrl(bindMaterial.elementsByTagName("instance_material").item(0).toElement().attribute("target"));
        geometry->setMaterial(world->getMaterials().value(id));
    }
}

NodePtr ColladaImporter::createNode(QDomElement element)
{
    // create new node
    WorldObjectPtr worldObject = getWorldObject(element);
    NodePtr node = worldObject.dynamicCast<Node>();
    Q_ASSERT(node);

    // set node properties
    node->setId(element.attribute("id"));
    node->setName(element.attribute("name"));
    node->setTransform(elementToMatrix4x4(element.firstChildElement("matrix")));

    if (GeometryPtr geometry = node.dynamicCast<Geometry>())
    {
        setGeoemetryNodeProperties(geometry,element.firstChildElement("instance_geometry"));
    }

    // recursively create child nodes
    QList<QDomElement> list;
    getChildElementsByTagName(element,"node",list);
    for (int loop = 0; loop < list.count(); loop++)
    {
        NodePtr childNode = createNode(list.at(loop));
        if (childNode)
        {
            Node::setParent(node,childNode);
        }
    }

    // return node
    return node;
}

CameraPtr ColladaImporter::createCamera(QDomElement element)
{
    CameraPtr camera = CameraPtr::create();
    camera->setId(element.attribute("id"));
    camera->setName(element.attribute("name"));
    QDomElement perspective = element.elementsByTagName("perspective").item(0).toElement();
    camera->setFieldOfView(perspective.firstChildElement("xfov").text().toFloat());
    camera->setAspectRatio(perspective.firstChildElement("aspect_ratio").text().toFloat());
    camera->setNearPlane(perspective.firstChildElement("znear").text().toFloat());
    camera->setFarPlane(perspective.firstChildElement("zfar").text().toFloat());

    return camera;
}

void ColladaImporter::loadCameras()
{
    QDomElement library = root.firstChildElement("library_cameras");
    QList<QDomElement> list;
    getChildElementsByTagName(library,"camera",list);
    for (int loop = 0; loop < list.count(); loop++)
    {
        CameraPtr camera = createCamera(list.at(loop));
        if (camera)
        {
            world->getCameras().insert(camera->getId(),camera);
        }
    }
}

PointLightPtr ColladaImporter::createPointLight(QDomElement element)
{
    PointLightPtr light = PointLightPtr::create();
    light->setColor(elementToColor(element.firstChildElement("color")));
    light->setConstantAttenuation(element.firstChildElement("constant_attenuation").text().toFloat());
    light->setLinearAttenuation(element.firstChildElement("linear_attenuation").text().toFloat());
    light->setQuadraticAttenuation(element.firstChildElement("quadratic_attenuation").text().toFloat());

    return light;
}


LightPtr ColladaImporter::createLight(QDomElement element)
{
    LightPtr light;
    QDomElement technique = element.firstChildElement("technique_common").firstChildElement();
    if (technique.tagName() == "point")
    {
        light = createPointLight(technique);
    }
    else
    {
        light = LightPtr::create();
    }
    light->setId(element.attribute("id"));
    light->setName(element.attribute("name"));

    return light;
}

void ColladaImporter::loadLights()
{
    QDomElement library = root.firstChildElement("library_lights");
    QList<QDomElement> list;
    getChildElementsByTagName(library,"light",list);
    for (int loop = 0; loop < list.count(); loop++)
    {
        LightPtr light = createLight(list.at(loop));
        if (light)
        {
            world->getLights().insert(light->getId(),light);
        }
    }
}

ImagePtr ColladaImporter::createImage(QDomElement element)
{
    ImagePtr image = ImagePtr::create();
    image->setId(element.attribute("id"));
    image->setName(element.attribute("name"));
    QDomElement pathElem = element.firstChildElement("init_from");
    if (!pathElem.isNull())
    {
        QString path = dir.filePath(pathElem.text());
        image->setImage(QImage(path));
    }

    return image;
}

void ColladaImporter::loadImages()
{
    QDomElement library = root.firstChildElement("library_images");
    QList<QDomElement> list;
    getChildElementsByTagName(library,"image",list);
    for (int loop = 0; loop < list.count(); loop++)
    {
        ImagePtr image = createImage(list.at(loop));
        if (image)
        {
            world->getImages().insert(image->getId(),image);
        }
    }
}

EffectPtr ColladaImporter::createEffect(QDomElement element)
{
    EffectPtr effect = EffectPtr::create();
    effect->setId(element.attribute("id"));
    effect->setName(element.attribute("name"));

    return effect;
}

void ColladaImporter::loadEffects()
{
    QDomElement library = root.firstChildElement("library_effects");
    QList<QDomElement> list;
    getChildElementsByTagName(library,"effect",list);
    for (int loop = 0; loop < list.count(); loop++)
    {

        EffectPtr effect = createEffect(list.at(loop));
        if (effect)
        {
            world->getEffects().insert(effect->getId(),effect);
        }
    }
}

MaterialPtr ColladaImporter::createMaterial(QDomElement element)
{
    MaterialPtr material = MaterialPtr::create();
    material->setId(element.attribute("id"));
    material->setName(element.attribute("name"));

    QString effectId = getIdFromUrl(element.firstChildElement("instance_effect").attribute("url"));
    QDomElement effectsLibrary = root.firstChildElement("library_effects");
    QDomElement materialEffect = getChildWithId(effectsLibrary,effectId);

    // texture
    QDomNodeList textures = materialEffect.elementsByTagName("surface");
    for(int loop = 0; loop < textures.count(); loop++)
    {
        QString imageId = textures.item(loop).firstChildElement("init_from").text();
        QString textureId = imageId + "-sampler";
        TexturePtr texture = TexturePtr::create();
        texture->setId(textureId);
        texture->setName(textureId);
        texture->setImage(world->getImages().value(imageId));
        material->getTextures().insert(textureId, texture);
    }

    // phong
    QDomElement phong = materialEffect.elementsByTagName("phong").item(0).toElement();
    material->setEmission(elementToColor(phong.firstChildElement("emission").firstChildElement()));
    material->setAmbient(elementToColor(phong.firstChildElement("ambient").firstChildElement()));
    material->setDiffuse(elementToColor(phong.firstChildElement("diffuse").firstChildElement()));
    material->setSpecular(elementToColor(phong.firstChildElement("specular").firstChildElement()));
    material->setShininess(phong.firstChildElement("shininess").firstChildElement("float").text().toFloat());
    material->setRefractionIndex(phong.firstChildElement("index_of_refraction").firstChildElement("float").text().toFloat());

    return material;
}

void ColladaImporter::loadMaterials()
{
    QDomElement library = root.firstChildElement("library_materials");
    QList<QDomElement> list;
    getChildElementsByTagName(library,"material",list);
    for (int loop = 0; loop < list.count(); loop++)
    {
        MaterialPtr material = createMaterial(list.at(loop));
        if (material)
        {
            world->getMaterials().insert(material->getId(),material);
        }
    }
}

MeshPtr ColladaImporter::createMesh(QDomElement element)
{
    MeshPtr mesh = MeshPtr::create();
    mesh->setId(element.attribute("id"));
    mesh->setName(element.attribute("name"));

    QDomElement meshElement = element.firstChildElement("mesh");

    // get vertex and normal data
    QDomNodeList arrayNodes = element.elementsByTagName("float_array");
    for(int loop = 0; loop < arrayNodes.count(); loop++)
    {
        QDomElement arrayElement = arrayNodes.item(loop).toElement();
        if (arrayElement.attribute("id").endsWith("positions-array"))
        {
            elementToFloatVector(arrayElement, mesh->getPositionData());
        }
        if (arrayElement.attribute("id").endsWith("normals-array"))
        {
            elementToFloatVector(arrayElement, mesh->getNormalData());
        }
        if (arrayElement.attribute("id").endsWith("map-0-array"))
        {
            elementToFloatVector(arrayElement, mesh->getUVData());
        }
    }

    // get poly info
    QDomElement polyElement = meshElement.firstChildElement("polylist");
    elementToUIntVector(polyElement.firstChildElement("vcount"), mesh->getPolyVertexCounts());
    elementToUIntVector(polyElement.firstChildElement("p"),mesh->getPolyVertexIndices());

    return mesh;
}

GeometryPtr ColladaImporter::createGeometry(QDomElement element)
{
    GeometryPtr geometry;
    if (element.firstChildElement().tagName() == "mesh")
    {
        geometry = createMesh(element);
    }
    else
    {
        geometry = GeometryPtr::create();
        geometry->setId(element.attribute("id"));
        geometry->setName(element.attribute("name"));
    }

    return geometry;
}

void ColladaImporter::loadGeometries()
{
    QDomElement library = root.firstChildElement("library_geometries");
    QList<QDomElement> list;
    getChildElementsByTagName(library,"geometry",list);
    for (int loop = 0; loop < list.count(); loop++)
    {
        GeometryPtr geometry = createGeometry(list.at(loop));
        if (geometry)
        {
            world->getGeometries().insert(geometry->getId(),geometry);
        }
    }
}

ControllerPtr ColladaImporter::createController(QDomElement element)
{
    ControllerPtr controller = ControllerPtr::create();
    controller->setId(element.attribute("id"));
    controller->setName(element.attribute("name"));

    return controller;
}

void ColladaImporter::loadControllers()
{
    QDomElement library = root.firstChildElement("library_controllers");
    QList<QDomElement> list;
    getChildElementsByTagName(library,"controller",list);
    for (int loop = 0; loop < list.count(); loop++)
    {
        ControllerPtr controller = createController(list.at(loop));
        if (controller)
        {
            world->getControllers().insert(controller->getId(),controller);
        }
    }
}

ScenePtr ColladaImporter::createScene(QDomElement element)
{
    ScenePtr scene = ScenePtr::create();
    scene->setId(element.attribute("id"));
    scene->setName(element.attribute("name"));

    QList<QDomElement> list;
    getChildElementsByTagName(element,"node",list);
    for (int loop = 0; loop < list.count(); loop++)
    {
        NodePtr node = createNode(list.at(loop));
        if (node)
        {
            if (CameraPtr camera = node.dynamicCast<Camera>())
                scene->getCameras().insert(node->getId(), camera);
            else if (LightPtr light = node.dynamicCast<Light>())
                scene->getLights().insert(node->getId(), light);
            else if (MeshPtr mesh = node.dynamicCast<Mesh>())
                scene->getMeshes().insert(node->getId(), mesh);
        }

    }

    return scene;
}

void ColladaImporter::loadScenes()
{
    QDomElement library = root.firstChildElement("library_visual_scenes");
    QList<QDomElement> list;
    getChildElementsByTagName(library,"visual_scene",list);
    for (int loop = 0; loop < list.count(); loop++)
    {
        ScenePtr scene = createScene(list.at(loop));
        if (scene)
        {
            world->getScenes().insert(scene->getId(),scene);
        }
    }
}

WorldPtr ColladaImporter::importWorld(QString path)
{
    // store the path for later
    this->dir = QDir(path);
    this->dir.cdUp();

    // open file
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return WorldPtr();
    file.close();

    // initialize dom doc
    QDomDocument doc;
    if (!doc.setContent((QIODevice*)&file)) return WorldPtr();

    // get the document root
    root = doc.firstChildElement("COLLADA");;
    if (root.isNull()) return WorldPtr();

    world = WorldPtr::create();
    // load the libraries - order is important
    loadCameras();
    loadLights();
    loadImages();
    //loadEffects(); // currently subsumed by materials
    loadMaterials();
    loadGeometries();
    loadControllers();
    loadScenes();

    return world;
}

