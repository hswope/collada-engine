#include "openglwidget.h"

#include <iostream>
#include <QOpenGLShader>
#include <QOpenGLVertexArrayObject>
#include <QKeyEvent>
#include <world/light/pointlight.h>

#define TEST_SCENE false

OpenGLWidget::OpenGLWidget(QWidget *parent) : QOpenGLWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);

    isWireFrame = false;
}

OpenGLWidget::~OpenGLWidget()
{
    makeCurrent();

    world->destroyGL();

    delete shaderProgram;
    delete fragmentShader;
    delete vertexShader;

    doneCurrent();
}

void OpenGLWidget::toggleWireframe()
{
    isWireFrame = !isWireFrame;
    update();
}

ScenePtr OpenGLWidget::getScene() const
{
    return scene;
}

void OpenGLWidget::setScene(ScenePtr scene)
{
    this->scene = scene;
}


WorldPtr OpenGLWidget::getWorld()
{
    return world;
}

void OpenGLWidget::setWorld(WorldPtr world)
{
    this->world = world;

    if (TEST_SCENE) this->world = createTestWorld();

    if (this->world)
    {
        initializeWorld();
        setScene(this->world->getScenes().value("Scene"));
        //this->scene->getCamera()->reset();
        resizeGL(width(),height());
    }
}

WorldPtr OpenGLWidget::createTestWorld()
{
    WorldPtr world = WorldPtr::create();

    // create camera
    CameraPtr camera = CameraPtr(new Camera());
    camera->setId("Camera1-camera");
    camera->setName("Camera");
    camera->setFieldOfView(50);
    camera->setAspectRatio(4/3);
    camera->setNearPlane(.1);
    camera->setFarPlane(100);
    world->getCameras().insert(camera->getId(),camera);

    // creat mesh
    MeshPtr mesh = MeshPtr::create();
    mesh->setId("Triangle-mesh");
    mesh->setName("Triangle");
    float triangle[] = {
        0.0f, 0.8f, 0.0f,
        -0.8f, -0.8f, 0.0f,
        0.8f, -0.8f, 0.0f
    };
    memcpy(mesh->getPositionData().data(),triangle,9*sizeof(float));
    mesh->getPolyVertexCounts().append(3);
    int idxs[] = {0,1,2};
    mesh->getPolyVertexIndices().resize(3);
    memcpy(mesh->getPolyVertexIndices().data(),idxs,3 * sizeof(int));
    world->getGeometries().insert(mesh->getId(),mesh);
    
    ScenePtr scene = ScenePtr::create();
    scene->setId("Scene");
    scene->setName("Scene");
    
    CameraPtr cameraNode = camera->clone().dynamicCast<Camera>();
    cameraNode->setId("Camera1");
    cameraNode->setName("Camera1");
    cameraNode->getTransform() = QMatrix4x4();
    scene->getCameras().insert(cameraNode->getId(), cameraNode.dynamicCast<Camera>());
    
    MeshPtr meshNode = mesh->clone().dynamicCast<Mesh>();
    meshNode->setId("Triangle1");
    meshNode->setName("Trangle");
    meshNode->getTransform() = QMatrix4x4();
    scene->getMeshes().insert(meshNode->getId(), meshNode.dynamicCast<Mesh>());

    world->getScenes().insert(scene->getId(),scene);

    return world;
}

// requires a current opengl context
void OpenGLWidget::initializeShaderProgram(MeshPtr mesh)
{
    mesh->getVao()->bind();
    shaderProgram->bind();

    mesh->getVertexBuffer()->bind();
    shaderProgram->enableAttributeArray("vert");
    shaderProgram->setAttributeArray("vert", GL_FLOAT, NULL, 3, 0);
    mesh->getVertexBuffer()->release();

    mesh->getNormalBuffer()->bind();
    shaderProgram->enableAttributeArray("vertNormal");
    shaderProgram->setAttributeArray("vertNormal", GL_FLOAT, NULL, 3, 0);
    mesh->getNormalBuffer()->release();

    mesh->getUVBuffer()->bind();
    shaderProgram->enableAttributeArray("vertTexCoord");
    shaderProgram->setAttributeArray("vertTexCoord", GL_FLOAT, NULL, 2, 0);
    mesh->getUVBuffer()->release();

    shaderProgram->release();
    mesh->getVao()->release();
}

void OpenGLWidget::initializeWorld()
{
    makeCurrent();

    world->initializeGL();
    foreach (GeometryPtr geometry, world->getGeometries())
    {
        if (MeshPtr mesh = geometry.dynamicCast<Mesh>())
            initializeShaderProgram(mesh);
    }

    doneCurrent();
}


void OpenGLWidget::initializeGL()
{
    // initialize opengl
    initializeOpenGLFunctions();

    // print out some info about the graphics drivers
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;

    // set clear color
    glClearColor(.5, .5, .5, 1);

    // load and compile shaders
    vertexShader = new QOpenGLShader(QOpenGLShader::Vertex);
    vertexShader->compileSourceFile(":/shader/shader.vert");
    fragmentShader = new QOpenGLShader(QOpenGLShader::Fragment);
    fragmentShader->compileSourceFile(":/shader/shader.frag");

    // add shaders to shader program, link them, and bind to the opengl context
    shaderProgram = new QOpenGLShaderProgram();
    shaderProgram->addShader(vertexShader);
    shaderProgram->addShader(fragmentShader);
    shaderProgram->link();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}

void OpenGLWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);

    if (scene)
    {
        scene->getCamera()->setAspectRatio((float)w/h);
    }
}

void OpenGLWidget::renderFrameMesh(MeshPtr mesh)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    // provide the model matrix
    shaderProgram->setUniformValue("model",mesh->getAbsoluteTransform());

    // set the material properties
    QSharedPointer<QOpenGLTexture> texture;
    MaterialPtr material = mesh->getMaterial();
    if (material)
    {
        shaderProgram->setUniformValue("materialEmissionColor", material->getEmission().toQVector3D());
        shaderProgram->setUniformValue("materialAmbientColor", material->getAmbient().toQVector3D());
        shaderProgram->setUniformValue("materialSpecularColor", material->getSpecular().toQVector3D());
        shaderProgram->setUniformValue("materialShininess", material->getShininess());
        shaderProgram->setUniformValue("materialRefractionIndex", material->getRefractionIndex());
        if (material->getDiffuse().getTextureId().isNull())
        {
            shaderProgram->setUniformValue("materialDiffuseColor", material->getDiffuse().toQVector3D());
        }
        else
        {
            texture = material->getTextures().value(material->getDiffuse().getTextureId())->getImage()->getOpenGLTexture();
            glActiveTexture(GL_TEXTURE0);
            texture->bind(0);
            shaderProgram->setUniformValue("materialTex", 0);
        }
    }

    // draw triangle
    mesh->getVao()->bind();
    if (texture)
    glDrawArrays(GL_TRIANGLES, 0, mesh->getPolyCount() * 3);
    mesh->getVao()->release();

    if (texture) texture->release();
    // paint all children
    foreach(NodePtr node, mesh->getNodes())
    {
        if (MeshPtr mesh = node.dynamicCast<Mesh>())
        {
            //paintMesh(mesh);
        }
    }
}


void OpenGLWidget::setFrameCamera(CameraPtr camera)
{
    // get the camera
    shaderProgram->setUniformValue("camera",camera->getMatrix());
    shaderProgram->setUniformValue("cameraPosition",camera->getPosition());
}

void OpenGLWidget::setFrameLight(LightPtr light)
{
    PointLightPtr pointLight = light.dynamicCast<PointLight>();
    if (pointLight)
    {
        shaderProgram->setUniformValue("pointLightPosition",pointLight->getPosition());
        shaderProgram->setUniformValue("pointLightColor",pointLight->getColor().toQVector3D());
        shaderProgram->setUniformValue("pointLightAttenuation",pointLight->getQuadraticAttenuation());
        shaderProgram->setUniformValue("pointLightAmbientCoeficient",0.005f);
    }
}

void OpenGLWidget::paintGL()
{
    // turn on wireframe
    if (isWireFrame)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    // clear
    glClear(GL_COLOR_BUFFER_BIT);

    // render scene
    if (scene)
    {
        // bind the shader program
        shaderProgram->bind();

        // set camera
        setFrameCamera(scene->getCamera());

        // set lighting
        foreach(LightPtr light, scene->getLights())
        {
            setFrameLight(light);
        }

        // draw meshes
        foreach(MeshPtr mesh, scene->getMeshes())
        {
            renderFrameMesh(mesh);
        }

        // unbind shader program
        shaderProgram->release();
    }

    // turn off wireframe
    if (isWireFrame)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

}

void OpenGLWidget::mouseButtonEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) == Qt::LeftButton)
    {
        leftButtonStartPoint = event->pos();
    }

}

void OpenGLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (scene && (event->buttons() & Qt::LeftButton) == Qt::LeftButton)
    {
        int deltaX = event->x() - leftButtonStartPoint.x();
        int deltaY = event->y() - leftButtonStartPoint.y();

        scene->getCamera()->offsetOrientation(-(float)deltaY / 100, -(float)deltaX / 100);
        update();
    }


    QWidget::mouseMoveEvent(event);
}


void OpenGLWidget::wheelEvent(QWheelEvent *event)
{
    if (scene && event->delta() > 0)
    {
        scene->getCamera()->offestPosition(MOVE_SPEED * scene->getCamera()->getForward());
        update();
    }
    else
    {
        scene->getCamera()->offestPosition(MOVE_SPEED * -scene->getCamera()->getForward());
        update();
    }
    QWidget::wheelEvent(event);
}

void OpenGLWidget::keyPressEvent(QKeyEvent *event)
{
    if (!scene)
    {
        QOpenGLWidget::keyPressEvent(event);
        return;
    }

    QVector3D vec;
    switch (event->key())
    {
        case Qt::Key_A:
            // move left
            scene->getCamera()->offestPosition(MOVE_SPEED * -scene->getCamera()->getRight());
            update();
            break;
        case Qt::Key_W:
            // move forward
            scene->getCamera()->offestPosition(MOVE_SPEED * scene->getCamera()->getForward());
            update();
            break;
        case Qt::Key_D:
            // move right
            scene->getCamera()->offestPosition(MOVE_SPEED * scene->getCamera()->getRight());
            update();
            break;
        case Qt::Key_S:
            // move back
            scene->getCamera()->offestPosition(MOVE_SPEED * -scene->getCamera()->getForward());
            update();
            break;
        case Qt::Key_Z:
            // move up
            scene->getCamera()->offestPosition(MOVE_SPEED * -QVector3D(0,1,0));
            update();
            break;
        case Qt::Key_X:
            // move down
            scene->getCamera()->offestPosition(MOVE_SPEED * QVector3D(0,1,0));
            update();
            break;
        case Qt::Key_R:
            // move down
            scene->getCamera()->reset();
            update();
            break;
        case Qt::Key_O:
            // move down
             scene->getCamera()->lookAt(vec);
            update();
            break;
        default:
            QOpenGLWidget::keyPressEvent(event);
    }
}
