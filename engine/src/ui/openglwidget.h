#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include "../world/world.h"

class QOpenGLShader;
class QOpenGLShaderProgram;
class QKeyEvent;
class QMouseEvent;
class QWheelEvent;

class OpenGLWidget : public QOpenGLWidget, protected QOpenGLFunctions
{
    Q_OBJECT

    static const int MOVE_SPEED = 1;

public:
    OpenGLWidget(QWidget *parent = 0);
    ~OpenGLWidget();
    void toggleWireframe();

    WorldPtr getWorld();
    void setWorld(WorldPtr world);

protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();

    virtual void keyPressEvent(QKeyEvent *event);
    virtual void mouseButtonEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);

private:
    bool isWireFrame;
    QPoint leftButtonStartPoint;

    QOpenGLShader* vertexShader;
    QOpenGLShader* fragmentShader;
    QOpenGLShaderProgram* shaderProgram;

    ScenePtr scene;
    WorldPtr world;

    ScenePtr getScene() const;
    void setScene(ScenePtr scene);

    void initializeWorld();
    void initializeShaderProgram(MeshPtr mesh);

    void setFrameCamera(CameraPtr camera);
    void setFrameLight(LightPtr light);
    void renderFrameMesh(MeshPtr mesh);


    WorldPtr createTestWorld();
};

#endif // OPENGLWIDGET_H
