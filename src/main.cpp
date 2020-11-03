#include "mainwindow.h"

#include <QApplication>
#include <QDateTime>
#include <QRandomGenerator>

int main(int argc, char *argv[])
{
    //int seed = QDateTime::currentMSecsSinceEpoch() / 1000;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
