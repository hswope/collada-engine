#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "openglwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog about(this);
    about.exec();
}

void MainWindow::on_actionOpen_triggered()
{

}

void MainWindow::on_actionWireframe_triggered()
{
    OpenGLWidget* openGLWidget = findChild<OpenGLWidget*>("openGLWidget");
    openGLWidget->toggleWireframe();
}
