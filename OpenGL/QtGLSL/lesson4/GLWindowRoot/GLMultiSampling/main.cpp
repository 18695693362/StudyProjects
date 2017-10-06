#include <QApplication>
#include <QGLFormat>
#include "multisamplingglwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setOption(QSurfaceFormat::DebugContext);
    format.setSamples(4);
    format.setVersion(4,1);
    QSurfaceFormat::setDefaultFormat(format);

    //GOGLWidget widget(NULL,"DrawCMD",false);
    MultiSamplingGLWidget widget(NULL,"MultiSampling",false);
    widget.show();
    
    return a.exec();
}
