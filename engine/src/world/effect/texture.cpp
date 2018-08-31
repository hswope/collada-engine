#include "texture.h"

Texture::Texture()
{
}

Texture::~Texture()
{
}

WorldObjectPtr Texture::clone()
{
    TexturePtr obj = TexturePtr::create();
    obj->copy(*this);
    return obj;
}

void Texture::copy(const Texture &texture)
{
    WorldObject::copy(texture);
    this->image = texture.image;
}

ImagePtr Texture::getImage()
{
    return image;
}

void Texture::setImage(ImagePtr image)
{
    this->image = image;
}
