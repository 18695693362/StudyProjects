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
    ../../../common/gsimpletriangle.cpp \
    ../../../common/gtriangle.cpp \
    mglwidget_PolygonMode.cpp

HEADERS  += \
    ../../../common/glhelper.h \
    ../../../common/gsimpletriangle.h \
    ../../../common/gtriangle.h \
    mglwidget_PolygonMode.h

CONFIG += c++11

LIBS += opengl32.lib

FORMS    +=


RESOURCES += \
    shaders.qrc

#win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../../libs/glm/release/ -lglm
#else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../../libs/glm/debug/ -lglm
#else:unix: LIBS += -L$$OUT_PWD/../../../libs/glm/ -lglm

INCLUDEPATH += $$PWD/../../../libs/glm
DEPENDPATH += $$PWD/../../../libs/glm

#win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../../libs/glm/release/libglm.a
#else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../../libs/glm/debug/libglm.a
#else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../../libs/glm/release/glm.lib
#else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../../libs/glm/debug/glm.lib
#else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../../libs/glm/libglm.a
