#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "GameUI.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startGame(int);

private:
    
    GameUI *_ui;
    QPushButton *_button;
    QSharedPointer<GameInterface> _game;
};
#endif // MAINWINDOW_H
