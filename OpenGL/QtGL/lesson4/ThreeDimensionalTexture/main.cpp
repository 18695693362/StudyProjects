#include "mglwidget.h"
#include <QApplication>
#include "glextensions.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MGLWidget widget(NULL,"My OpenGL Window",false);
    widget.makeCurrent();

    if(!getGLExtensionFunctions().resolve(widget.context()))
    {
        QMessageBox::information(0, "Unsupport OpenGL Extension!", "OK");
    }
    else
    {
        widget.show();
    }
    return a.exec();
}
