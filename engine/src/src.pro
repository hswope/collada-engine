#-------------------------------------------------
#
# Project created by QtCreator 2015-04-08T14:32:15
#
#-------------------------------------------------
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets xml

TARGET = FinalProject
TEMPLATE = app

SOURCES += main.cpp\
    ui/aboutdialog.cpp \
    ui/mainwindow.cpp \
    ui/openglwidget.cpp \
    world/camera.cpp \
    world/colladaimporter.cpp \
    world/light/light.cpp \
    world/effect/material.cpp \
    world/geometry/mesh.cpp \
    world/node.cpp \
    world/scene.cpp \
    world/effect/texture.cpp \
    world/world.cpp \
    world/geometry/geometry.cpp \
    world/effect/effect.cpp \
    world/controller.cpp \
    world/effect/image.cpp \
    world/worldobject.cpp \
    world/light/pointlight.cpp \
    world/effect/color.cpp

HEADERS  += ui/aboutdialog.h \
    ui/mainwindow.h \
    ui/openglwidget.h \
    global.h \
    scene/world.h \
    world/camera.h \
    world/colladaimporter.h \
    world/light/light.h \
    world/effect/material.h \
    world/geometry/mesh.h \
    world/node.h \
    world/scene.h \
    world/effect/texture.h \
    world/world.h \
    world/geometry/geometry.h \
    world/effect/effect.h \
    world/controller.h \
    world/effect/image.h \
    world/worldobject.h \
    world/light/pointlight.h \
    world/effect/color.h

FORMS    += ui/aboutdialog.ui \
    ui/mainwindow.ui

DISTFILES +=

RESOURCES += \
    res/res.qrc \
