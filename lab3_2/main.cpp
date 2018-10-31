#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    w.setFixedHeight(161);
    w.setFixedWidth(411);

    return a.exec();
}
