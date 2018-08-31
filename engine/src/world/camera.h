#ifndef CAMERA_H
#define CAMERA_H

#include "node.h"

class Camera;
typedef QSharedPointer<Camera> CameraPtr;

class Camera : public Node
{
    static const float MAX_VERTICAL_ANGLE;

public:
    explicit Camera();
    virtual ~Camera();

    virtual WorldObjectPtr clone();

    float getFieldOfView() const;
    void setFieldOfView(float fieldOfView);
    float getAspectRatio() const;
    void setAspectRatio(float aspectRatio);
    float getNearPlane() const;
    void setNearPlane(float nearPlane);
    float getFarPlane() const;
    void setFarPlane(float farPlane);

    float getVerticalAngle() const;
    void setVerticalAngle(float angle);
    float getHorizontalAngle() const;
    void setHorizontalAngle(float angle);

    QVector3D const &getPosition() const;
    void setPosition(QVector3D const &position);
    void offestPosition(const QVector3D &offset);
    QMatrix4x4 getOrientation() const;
    void offsetOrientation(float upAngle, float rightAngle);
    void lookAt(QVector3D position);
    QVector3D getForward() const;
    QVector3D getRight() const;
    QVector3D getUp() const;
    QMatrix4x4 getMatrix() const;
    QMatrix4x4 getProjection() const;
    QMatrix4x4 getView() const;
    void reset();


protected:
    virtual void copy(const Camera &camera);

private:

    float fieldOfView;
    float aspectRatio;
    float nearPlane;
    float farPlane;

    QVector3D position;
    float verticalAngle;
    float horizontalAngle;

    void normalizeAngles();

};


#endif // CAMERA_H
