cmake_minimum_required(VERSION 3.1)

# Check if environment variable QTDIR is set.
if (DEFINED ENV{QTDIR})
    set(CMAKE_PREFIX_PATH $ENV{QTDIR} ${CMAKE_PREFIX_PATH})
else ()
    message (FATAL_ERROR "ERROR: Environment variable QTDIR is not set. Please locate your Qt folder")
endif ()

project(finalproject)
set(COMPILE_DEFINITIONS DYLD_IMAGE_SUFFIX=_debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../bin")
set(CMAKE_MACOSX_BUNDLE ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(OpenGL)
find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5OpenGLExtensions)
find_package(Qt5Xml)
find_package(Qt5Widgets)
include_directories(../QtGenerated)
qt5_add_resources(RESOURCES res/res.qrc)

set(
    SOURCE_FILES
    main.cpp
    world/effect/color.cpp
    world/effect/color.h
    ui/mainwindow.cpp
    ui/mainwindow.h
    ui/aboutdialog.cpp
    ui/aboutdialog.h
    ui/openglwidget.cpp
    ui/openglwidget.h
    world/worldobject.cpp
    world/worldobject.h
    world/node.cpp
    world/node.h
    world/camera.cpp
    world/camera.h
    world/light/light.cpp
    world/light/light.h
    world/light/pointlight.cpp
    world/light/pointlight.h
    world/effect/image.cpp
    world/effect/image.h
    world/effect/effect.cpp
    world/effect/effect.h
    world/effect/material.cpp
    world/effect/material.h
    world/geometry/geometry.cpp
    world/geometry/geometry.h
    world/geometry/mesh.cpp
    world/geometry/mesh.h
    world/controller.cpp
    world/controller.h
    world/scene.cpp
    world/scene.h
    world/effect/texture.cpp
    world/effect/texture.h
    world/world.cpp
    world/world.h
    world/colladaimporter.cpp
    world/colladaimporter.h
)

add_executable(finalproject ${SOURCE_FILES} ${RESOURCES})
#qt5_use_modules(finalproject Widgets Gui Core Xml OpenGL)
target_link_libraries(finalproject Qt5::Widgets Qt5::Core Qt5::Gui Qt5::Xml ${OPENGL_LIBRARIES})