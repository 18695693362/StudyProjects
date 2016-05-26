#-------------------------------------------------
#
# Project created by QtCreator 2013-08-01T13:02:43
#
#-------------------------------------------------

QT       += core gui
QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GLWindow
TEMPLATE = app


SOURCES += main.cpp \
    ../../common/glhelper.cpp \
    mglwidget_UniformBlock.cpp

HEADERS  += \
    ../../common/glhelper.h \
    mglwidget_UniformBlock.h

CONFIG += c++11

FORMS    +=

OTHER_FILES += \
    ../README.txt

RESOURCES += \
    shaders.qrc
