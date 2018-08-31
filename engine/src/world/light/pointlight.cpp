#include "pointlight.h"

PointLight::PointLight()
{
}

PointLight::~PointLight()
{
}


WorldObjectPtr PointLight::clone()
{
    PointLightPtr obj = PointLightPtr::create();
    obj->copy(*this);
    return obj;
}

void PointLight::copy(const PointLight &pointLight)
{
    Light::copy(pointLight);
    this->color = pointLight.color;
    this->constantAttenuation = pointLight.constantAttenuation;
    this->linearAttenuation = pointLight.linearAttenuation;
    this->quadraticAttenuation = pointLight.quadraticAttenuation;
}

Color const &PointLight::getColor() const
{
    return color;
}

void PointLight::setColor(Color const &color)
{
    PointLight::color = color;
}

float PointLight::getConstantAttenuation() const
{
    return constantAttenuation;
}

void PointLight::setConstantAttenuation(float constantAttenuation)
{
    PointLight::constantAttenuation = constantAttenuation;
}

float PointLight::getLinearAttenuation() const
{
    return linearAttenuation;
}

void PointLight::setLinearAttenuation(float linearAttenuation)
{
    PointLight::linearAttenuation = linearAttenuation;
}

float PointLight::getQuadraticAttenuation() const
{
    return quadraticAttenuation;
}

void PointLight::setQuadraticAttenuation(float quadraticAttenuation)
{
    PointLight::quadraticAttenuation = quadraticAttenuation;
}
