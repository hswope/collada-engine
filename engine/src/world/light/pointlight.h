#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include <QColor>
#include "light.h"

class PointLight;
typedef QSharedPointer<PointLight> PointLightPtr;

class PointLight : public Light
{
public:
    PointLight();
    ~PointLight();

    virtual WorldObjectPtr clone();

    Color const &getColor() const;
    void setColor(Color const &color);
    float getConstantAttenuation() const;
    void setConstantAttenuation(float constantAttenuation);
    float getLinearAttenuation() const;
    void setLinearAttenuation(float linearAttenuation);
    float getQuadraticAttenuation() const;
    void setQuadraticAttenuation(float quadraticAttenuation);

protected:
    void copy(const PointLight& pointLight);

private:
    Color color;
    float constantAttenuation;
    float linearAttenuation;
    float quadraticAttenuation;

};

#endif // POINTLIGHT_H
