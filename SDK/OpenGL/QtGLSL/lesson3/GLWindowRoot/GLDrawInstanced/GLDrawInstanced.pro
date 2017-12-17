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
    ../../../common/vbm.cpp \
    mglwidget_DrawInstanced.cpp \
    testvbobject.cpp \
    ../../../common/gtriangle.cpp \
    ../../../common/gdebug.cpp \
    ginstancearray.cpp

HEADERS  += \
    ../../../common/glhelper.h \
    ../../../common/vbm.h \
    mglwidget_DrawInstanced.h \
    testvbobject.h \
    ../../../common/gtriangle.h \
    ../../../common/gdebug.h \
    ginstancearray.h \
    ../../../common/glfuncdefine.h

CONFIG += c++11

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

G_RES_DIR = "res"
G_SRC_DIR = $${PWD}/$${G_RES_DIR}
G_DES_DIR = $${OUT_PWD}/$${G_RES_DIR}
win32 {
    G_SRC_DIR ~= s,/,\\,g
    G_DES_DIR ~= s,/,\\,g
    copyfiles.commands = $$quote(cmd /c xcopy /Y /S /E /I $${G_SRC_DIR} $${G_DES_DIR})
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
