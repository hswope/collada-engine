#include <math.h>
#include "camera.h"

const float Camera::MAX_VERTICAL_ANGLE = 85.0f;

Camera::Camera()
{
}

Camera::~Camera()
{
}

WorldObjectPtr Camera::clone()
{
    CameraPtr obj = CameraPtr::create();
    obj->copy(*this);
    return obj;
}

void Camera::copy(const Camera &camera)
{
    Node::copy(camera);
    fieldOfView = camera.fieldOfView;
    aspectRatio = camera.aspectRatio;
    nearPlane = camera.nearPlane;
    farPlane = camera.farPlane;

    verticalAngle = camera.verticalAngle;
    horizontalAngle = camera.horizontalAngle;
}

float Camera::getFieldOfView() const
{
    return fieldOfView;
}

void Camera::setFieldOfView(float fieldOfView)
{
    this->fieldOfView = fieldOfView;
}

float Camera::getAspectRatio() const
{
    return aspectRatio;
}

void Camera::setAspectRatio(float aspectRatio)
{
    this->aspectRatio = aspectRatio;
}

float Camera::getNearPlane() const
{
    return nearPlane;
}

void Camera::setNearPlane(float nearPlane)
{
    this->nearPlane = nearPlane;
}

float Camera::getFarPlane() const
{
    return farPlane;
}

void Camera::setFarPlane(float farPlane)
{
    this->farPlane = farPlane;
}

float Camera::getVerticalAngle() const
{
    return verticalAngle;
}

void Camera::setVerticalAngle(float angle)
{
    this->verticalAngle = angle;
}

float Camera::getHorizontalAngle() const
{
    return horizontalAngle;
}

void Camera::setHorizontalAngle(float angle)
{
    this->horizontalAngle = angle;
}

QVector3D const &Camera::getPosition() const
{
    return position;
}

void Camera::setPosition(QVector3D const &position)
{
   this->position = position;
}

void Camera::offestPosition(const QVector3D &offset)
{
    position += offset;
}

QMatrix4x4 Camera::getOrientation() const
{
    QMatrix4x4 orientation;
    orientation.rotate(verticalAngle,1,0,0);
    orientation.rotate(horizontalAngle,0,1,0);
    return orientation;
}

void Camera::offsetOrientation(float upAngle, float rightAngle)
{
    horizontalAngle += rightAngle;
    verticalAngle += upAngle;
    normalizeAngles();
}

void Camera::lookAt(QVector3D position)
{
    if (this->position == position) return;
    QVector3D direction = position - this->position;
    direction.normalize();
    verticalAngle = asinf(-direction.y());
    horizontalAngle = atan2f(-direction.x(),-direction.z());
    normalizeAngles();
}

QVector3D Camera::getForward() const
{
    QVector4D up = getOrientation().inverted() * QVector4D(0,0,-1,1);
    return QVector3D(up);
}

QVector3D Camera::getRight() const
{
    QVector4D up = getOrientation().inverted() * QVector4D(1,0,0,1);
    return QVector3D(up);
}

QVector3D Camera::getUp() const
{
    QVector4D up = getOrientation().inverted() * QVector4D(0,1,0,1);
    return QVector3D(up);
}

QMatrix4x4 Camera::getMatrix() const
{
    return getProjection() * getView();
}

QMatrix4x4 Camera::getProjection() const
{
    QMatrix4x4 mat;
    mat.perspective(fieldOfView,aspectRatio,nearPlane,farPlane);
    return mat;
}

QMatrix4x4 Camera::getView() const
{
    QMatrix4x4 mat;
    mat.translate(-getPosition());
    return getOrientation() * mat;
}

void Camera::normalizeAngles()
{
    horizontalAngle = fmodf(horizontalAngle,360.0f);
    if (horizontalAngle < 0.0f)
        horizontalAngle += 360.0f;

    if (verticalAngle > MAX_VERTICAL_ANGLE)
        verticalAngle = MAX_VERTICAL_ANGLE;
    else if (verticalAngle < -MAX_VERTICAL_ANGLE)
        verticalAngle = -MAX_VERTICAL_ANGLE;
}

void Camera::reset()
{
    setPosition(QVector3D() * getAbsoluteTransform());
    lookAt(QVector3D());
}
