#include "mainwindow.h"

#include <QApplication>
#include <QDateTime>
#include <QRandomGenerator>
#include <time.h>
#include <vld.h>

#include "MoveInterface.h"

int main(int argc, char *argv[])
{
    qRegisterMetaType<MovePtr>("MovePtr");
    srand(time(NULL));
    //int seed = QDateTime::currentMSecsSinceEpoch() / 1000;
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
