#-------------------------------------------------
#
# Project created by QtCreator 2013-08-01T13:02:43
#
#-------------------------------------------------
QT       += core gui widgets

TARGET = GLWindow
TEMPLATE = app


SOURCES += main.cpp \
    mglwidget.cpp \
    ../../common/glhelper.cpp

HEADERS  += \
    mglwidget.h \
    ../../common/glhelper.h

CONFIG += c++11

FORMS    +=

OTHER_FILES += \
    README.txt

RESOURCES += \
    shaders.qrc