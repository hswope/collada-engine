#ifndef COLOR_H
#define COLOR_H

#include <QColor>

class Color
{
public:
    Color();

    Color(QColor color);
    Color(QString textureId);

    QColor getColor() const;
    void setColor(QColor color);
    QString getTextureId() const;
    void setTextureId(QString textureId);

    QVector4D toQVector4D() const;
    QVector3D toQVector3D() const;

private:
    QColor color;
    QString textureId;
};

#endif // COLOR_H
