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
    goglwidget.cpp \
    ../../../common/gcubemaptexture.cpp \
    ../../../common/gcube.cpp \
    ../../../common/gcamera.cpp

HEADERS  += \
    ../../../common/glhelper.h \
    ../../../common/gdebug.h \
    ../../../common/gtriangle.h \
    goglwidget.h \
    ../../../common/gcubemaptexture.h \
    ../../../common/gcube.h \
    ../../../common/gcamera.h

CONFIG += c++11

FORMS    +=


RESOURCES += \
    shaders.qrc

INCLUDEPATH += $$PWD/../../../libs/glm
DEPENDPATH += $$PWD/../../../libs/glm

DISTFILES += \
    ../../../TIPS.txt \
    ../../README.txt

RES_DIR = "res"
G_SRC_DIR = $${PWD}/$${G_RES_DIR}
G_DES_DIR = $${OUT_PWD}/$${G_RES_DIR}
win32 {
    G_SRC_DIR ~= s,/,\\,g
    G_DES_DIR ~= s,/,\\,g
    copyfiles.commands = $$quote(cmd /c xcopy /Y /S /I $${G_SRC_DIR} $${G_DES_DIR})
}
macx {
    copyfiles.commands = cp -r $$G_SRC_DIR $$G_DES_DIR
}
linux {
    copyfiles.commands = cp -r $$G_SRC_DIR $$G_DES_DIR
}
QMAKE_EXTRA_TARGETS += copyfiles
POST_TARGETDEPS += copyfiles
QMAKE_EXTRA_TARGETS += copyfiles
POST_TARGETDEPS += copyfiles
