#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMenuBar>
#include <QMenu>
#include <QSharedPointer>
#include <QScopedPointer>
#include <QLayout>
class NewGameDialog;
class GameUI;
class GameController;
class GameInterface;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QSharedPointer<GameInterface> game() const;
    void setGame(const QSharedPointer<GameInterface> &game);

private slots:
    void newGame();

private:
    
    void setMenus();

    QSharedPointer<GameInterface> _game;
    QSharedPointer<GameUI> _ui;
    QSharedPointer<GameController> _controller;
    QSharedPointer<NewGameDialog> _gameDialog;

    QMenu *_menuFile;
    QAction* _newGame;
    QAction* _startGame;
    QHBoxLayout *_hlayout;

};
#endif // MAINWINDOW_H
