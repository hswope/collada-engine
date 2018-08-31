#ifndef MATERIAL_H
#define MATERIAL_H

#include "../worldobject.h"
#include <QMap>
#include "texture.h"

class Material;
typedef QSharedPointer<Material> MaterialPtr;

class Material : public WorldObject
{
public:
    explicit Material();
    ~Material();

    virtual WorldObjectPtr clone();

    Color const &getEmission() const;
    void setEmission(Color const &emission);
    Color const &getAmbient() const;
    void setAmbient(Color const &ambient);
    Color const &getDiffuse() const;
    void setDiffuse(Color const &diffuse);
    Color const &getSpecular() const;
    void setSpecular(Color const &specular);
    float getShininess() const;
    void setShininess(float shininess);
    float getRefractionIndex() const;
    void setRefractionIndex(float refractionIndex);

    QMap<QString,TexturePtr> &getTextures();

protected:
    void copy(const Material &material);

private:
    Color emission;
    Color ambient;
    Color diffuse;
    Color specular;
    float shininess;
    float refractionIndex;
    QMap<QString,TexturePtr> textures;

};

#endif // MATERIAL_H
