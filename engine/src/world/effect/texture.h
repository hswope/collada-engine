#ifndef TEXTURE_H
#define TEXTURE_H

#include "../worldobject.h"
#include "image.h"

class Texture;
typedef QSharedPointer<Texture> TexturePtr;

class Texture : public WorldObject
{
public:
    Texture();
    ~Texture();

    virtual WorldObjectPtr clone();

    ImagePtr getImage();
    void setImage(ImagePtr image);

protected:
    void copy(const Texture &texture);

private:
    ImagePtr image;

};

#endif // TEXTURE_H
