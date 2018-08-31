#include "ui/mainwindow.h"
#include <QApplication>
#include <QSurfaceFormat>
#include <world/colladaimporter.h>
#include "ui/openglwidget.h"

#define colladafile "/Users/hswope/Documents/Villanova/csc8470/repo/finalproject/models/cube5.dae"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // set default opengl settings
    QSurfaceFormat format;
    format.setVersion(4,1);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);

    QSurfaceFormat::setDefaultFormat(format);

    // create and show the main window
    MainWindow w;
    w.show();

    // load the world data
    ColladaImporter colladaImporter;
    WorldPtr world = colladaImporter.importWorld(colladafile);

    // give the ui its scene
    OpenGLWidget* openGLWidget = w.findChild<OpenGLWidget*>("openGLWidget");
    openGLWidget->setWorld(world);

    return a.exec();
}
