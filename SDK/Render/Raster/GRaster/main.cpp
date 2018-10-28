#include "graster.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GRaster w;
    w.show();

    return a.exec();
}
