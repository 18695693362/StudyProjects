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
    ../../../common/gtriangle.cpp \
    goglwidget.cpp

HEADERS  += \
    ../../../common/glhelper.h \
    ../../../common/gdebug.h \
    ../../../common/gtriangle.h \
    goglwidget.h

CONFIG += c++11

FORMS    +=


RESOURCES += \
    shaders.qrc

INCLUDEPATH += $$PWD/../../../libs/glm
DEPENDPATH += $$PWD/../../../libs/glm

DISTFILES += \
    ../../../TIPS.txt \
    ../../README.txt
