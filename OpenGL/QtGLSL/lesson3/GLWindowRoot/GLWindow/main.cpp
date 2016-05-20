#include "mglwidget_DrawCommands.h"
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

    MGLWidgetDrawCMD widget(NULL,"DrawCMD",false);
    widget.setFormat(format);
    widget.show();
    
    return a.exec();
}