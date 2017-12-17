#include "mglwidget_DrawElements.h"
#include <QApplication>
#include <QGLFormat>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setOption(QSurfaceFormat::DebugContext);
    format.setVersion(4,1);
    QSurfaceFormat::setDefaultFormat(format);

    MGLWidgetDrawElements widget(NULL,"DrawElements",false);
    widget.show();
    
    return a.exec();
}
