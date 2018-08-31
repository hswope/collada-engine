#include "image.h"

Image::Image()
{
}

Image::~Image()
{
}

WorldObjectPtr Image::clone()
{
    ImagePtr obj = ImagePtr::create();
    obj->copy(*this);
    return obj;
}

void Image::copy(const Image &image)
{
    WorldObject::copy(image);
    this->image = image.image;
}

QImage Image::getImage()
{
    return image;
}

void Image::setImage(QImage image)
{
    this->image = image;
}

QSharedPointer<QOpenGLTexture> Image::getOpenGLTexture()
{
    return openGLTexture;
}

void Image::initializeGL()
{
    WorldObject::initializeGL();
    openGLTexture = QSharedPointer<QOpenGLTexture>::create(image.mirrored());
    openGLTexture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    openGLTexture->setMagnificationFilter(QOpenGLTexture::Linear);
}

void Image::destroyGL()
{
    if (openGLTexture)
    {
        openGLTexture->destroy();
    }
}