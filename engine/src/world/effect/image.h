#ifndef IAMGE_H
#define IAMGE_H

#include <QImage>
#include <QOpenGLTexture>
#include "../worldobject.h"

class Image;
typedef QSharedPointer<Image> ImagePtr;

class Image : public WorldObject
{
public:
    Image();
    ~Image();

    QImage getImage();
    void setImage(QImage image);

    QSharedPointer<QOpenGLTexture> getOpenGLTexture();

    virtual WorldObjectPtr clone();
    virtual void initializeGL();
    virtual void destroyGL();

protected:
    void copy(const Image &image);

private:
    QImage image;
    QSharedPointer<QOpenGLTexture> openGLTexture;

};

#endif // IAMGE_H
