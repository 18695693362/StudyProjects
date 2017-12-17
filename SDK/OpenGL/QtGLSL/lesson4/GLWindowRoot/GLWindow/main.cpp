#include "goglwidget.h"
#include <QApplication>
#include <QGLFormat>
#include "vertexcolor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setOption(QSurfaceFormat::DebugContext);
    format.setVersion(4,1);
    QSurfaceFormat::setDefaultFormat(format);

    //GOGLWidget widget(NULL,"DrawCMD",false);
    VertexColor widget(NULL,"VertexColor",false);
    widget.show();
    
    return a.exec();
}
