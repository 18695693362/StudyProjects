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
    ../../../common/glhelper.cpp \
    ../../../common/gdebug.cpp \
    goglwidget.cpp \
    ../../../common/gcamera.cpp \
    ../../../common/gcube.cpp \
    ../../../common/gtimermgr.cpp

HEADERS  += \
    ../../../common/glhelper.h \
    ../../../common/gdebug.h \
    goglwidget.h \
    ../../../common/gcamera.h \
    ../../../common/gcube.h \
    ../../../common/gtimermgr.h

CONFIG += c++11

FORMS    +=


RESOURCES +=

INCLUDEPATH += $$PWD/../../../libs/glm
DEPENDPATH += $$PWD/../../../libs/glm

DISTFILES += \
    ../../../TIPS.txt \
    ../../README.txt
