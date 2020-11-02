#include "mainwindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    qDebug() << "test";
}

MainWindow::~MainWindow()
{
}

