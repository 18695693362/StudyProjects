#include "mglwidget.h"
#include <QApplication>
#include <QMessageBox>

#define kHelperInfo "\
1. Press Mouse To Change Element.\n\
2. Press Number Key To Change Different Mode!\n\
\
"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMessageBox::information(NULL,"Tips",kHelperInfo,QMessageBox::Ok);

    MGLWidget widget(NULL,"My OpenGL Window",false);
    widget.show();
    
    return a.exec();
}
