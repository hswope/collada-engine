#include "color.h"
#include <QVector4D>
#include <QVector3D>

Color::Color() { }


Color::Color(QColor color)
{
    this->color = color;
}

Color::Color(QString textureId)
{
    this->textureId = textureId;
}


QColor Color::getColor() const
{
    return color;
}

void Color::setColor(QColor color)
{
    this->color = color;
}

QString Color::getTextureId() const
{
    return textureId;
}

void Color::setTextureId(QString textureId)
{
    this->textureId = textureId;
}

QVector4D Color::toQVector4D() const
{
    qreal r, g, b, a;
    color.getRgbF(&r,&g,&b,&a);
    return QVector4D(r,g,b,a);
}

QVector3D Color::toQVector3D() const
{
    qreal r, g, b, a;
    color.getRgbF(&r,&g,&b,&a);
    return QVector3D(r,g,b);
}
