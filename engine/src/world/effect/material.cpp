#include "material.h"

Material::Material()
{
}

Material::~Material()
{
}

WorldObjectPtr Material::clone()
{
    MaterialPtr obj = MaterialPtr::create();
    obj->copy(*this);
    return obj;
}

void Material::copy(const Material &material)
{
    WorldObject::copy(material);
    this->emission = material.emission;
    this->ambient = material.ambient;
    this->diffuse = material.diffuse;
    this->specular = material.specular;
    this->shininess = material.shininess;
    this->refractionIndex = material.refractionIndex;
    this->textures = material.textures;
}

QMap<QString,TexturePtr> &Material::getTextures()
{
    return textures;
}

Color const &Material::getEmission() const
{
    return emission;
}

void Material::setEmission(Color const &emission)
{
    Material::emission = emission;
}

Color const &Material::getAmbient() const
{
    return ambient;
}

void Material::setAmbient(Color const &ambient)
{
    Material::ambient = ambient;
}

Color const &Material::getDiffuse() const
{
    return diffuse;
}

void Material::setDiffuse(Color const &diffuse)
{
    Material::diffuse = diffuse;
}

Color const &Material::getSpecular() const
{
    return specular;
}

void Material::setSpecular(Color const &specular)
{
    Material::specular = specular;
}

float Material::getShininess() const
{
    return shininess;
}

void Material::setShininess(float shininess)
{
    Material::shininess = shininess;
}

float Material::getRefractionIndex() const
{
    return refractionIndex;
}

void Material::setRefractionIndex(float refractionIndex)
{
    Material::refractionIndex = refractionIndex;
}
