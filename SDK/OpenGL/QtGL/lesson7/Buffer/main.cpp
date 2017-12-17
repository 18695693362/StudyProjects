#include "mglwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MGLWidget widget(NULL,"My OpenGL Window",false);
    widget.show();
    
    return a.exec();
}
