#include <QApplication>
#include <QGLFormat>
#include "mglwidget_DrawInstanced.h"
#include "testvbobject.h"
#include "ginstancearray.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGL);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setOption(QSurfaceFormat::DebugContext);
    format.setVersion(4,1);
    QSurfaceFormat::setDefaultFormat(format);

    //MGLWidgetDrawInstanced widget(NULL,"DrawCMD",false);
    GInstanceArray widget(NULL,"GInstanceArray",false);
    //TestVBObject widget(NULL,"TestVBObject",false);
    widget.show();
    
    return a.exec();
}
