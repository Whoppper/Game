#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QSharedPointer>

class GameUI;
class GameController;
class GameInterface;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void startGame(int);

private:
    
    //QSharedPointer<GameUI> _ui;
    //QSharedPointer<GameController> _controller;
    QSharedPointer<GameInterface> _game;
    GameUI *_ui;
    GameController *_controller;

};
#endif // MAINWINDOW_H
