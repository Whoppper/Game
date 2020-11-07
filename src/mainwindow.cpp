#include "mainwindow.h"
#include <QDebug>

#include "MoveInterface.h"
#include "GameInterface.h"
#include "IA.h"
#include "RandomAlgorithm.h"
#include "AlgorithmInterface.h"
#include "IA.h"
#include "Human.h"
#include "GameUI.h"
#include "GameController.h"
#include "ModelFactory.h"
#include "Fiar.h"
#include <QBoxLayout>
#include <QSharedPointer>
#include <QThread>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //QWidget *wid = new
    setMinimumSize(1000, 1000);

    //_button->setS
    _game= ModelFactory::create<Fiar>();
    _ui = new GameUI(this, _game);
    _button = new QPushButton("GO", this);
    //setLayout(new QVBoxLayout(this));
    //layout()->addWidget(_ui);
    //layout()->addWidget(_button);
    connect(_button, &QPushButton::clicked, this, &MainWindow::startGame);
}

void MainWindow::startGame(int)
{
    qDebug() << "start";


    GameController *gameController = new GameController(this);
    QSharedPointer<AlgorithmInterface> algop1 = ModelFactory::create<RandomAlgorithm>();
    QSharedPointer<AlgorithmInterface> algop2 = ModelFactory::create<RandomAlgorithm>();
    QSharedPointer<PlayerInterface> p1 (new IA(_game->clone(), algop1));
    QSharedPointer<PlayerInterface> p2 (new IA(_game->clone(), algop2));
    gameController->addPlayer(p1);
    gameController->addPlayer(p2);
    int turn = 0;
    while (!_game->finish())
    {
        p1->setGame(_game->clone());
        QSharedPointer<MoveInterface> move;
        move = p1->getMove();
        move->playInGame(_game);
        _ui->update();
        QThread::msleep(400);
        if (_game->finish())
        {
            break;
        }
        p2->setGame(_game->clone());
        move = p2->getMove();
        move->playInGame(_game);
        _ui->update();
        QThread::msleep(400);
        qDebug() << " tour "<< turn++;
        break;
    }
    qDebug() << "end";
}

MainWindow::~MainWindow()
{
    
}

