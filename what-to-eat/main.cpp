#include "widget.h"
#include "mainwindow1.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow1 M1;
    M1.show();

    return a.exec();
}
