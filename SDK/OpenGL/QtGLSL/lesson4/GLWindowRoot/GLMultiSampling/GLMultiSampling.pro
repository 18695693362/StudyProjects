
QT       += core gui
QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GLWindow
TEMPLATE = app

SOURCES += main.cpp \
    ../../../common/glhelper.cpp \
    ../../../common/gsimpletriangle.cpp \
    multisamplingglwidget.cpp \
    main.cpp

HEADERS  += \
    ../../../common/glhelper.h \
    ../../../common/gsimpletriangle.h \
    multisamplingglwidget.h

CONFIG += c++11

FORMS    +=


RESOURCES +=

INCLUDEPATH += $$PWD/../../../libs/glm
DEPENDPATH += $$PWD/../../../libs/glm

DISTFILES += \
    ../../../TIPS.txt \
    ../../README.org
