#include "mainwindow.h"

#include <QApplication>
#include <QDateTime>
#include <QRandomGenerator>
#include <time.h>

int main(int argc, char *argv[])
{
    srand(time(NULL));
    //int seed = QDateTime::currentMSecsSinceEpoch() / 1000;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
