#include "mglwidget.h"
#include <QApplication>
#include <QGLFormat>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QGLFormat format;
    format.setVersion(3,3);
    format.setProfile(QGLFormat::CoreProfile);
    QGLFormat::setDefaultFormat(format);

    MGLWidget widget(NULL,"My OpenGL Window",false);
    widget.show();
    
    return a.exec();
}
