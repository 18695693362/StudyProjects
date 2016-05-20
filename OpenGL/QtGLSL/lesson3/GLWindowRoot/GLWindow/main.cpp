#include "mglwidget_DrawCommands.h"
#include <QApplication>
#include <QGLFormat>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGLFormat format;
    format.setVersion(4,1);
    format.setProfile(QGLFormat::CoreProfile);
    QGLFormat::setDefaultFormat(format);

    MGLWidgetUniformBlock widget(NULL,"DrawCMD",false);
    widget.show();
    
    return a.exec();
}
