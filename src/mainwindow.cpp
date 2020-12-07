#include "mainwindow.h"
#include <QDebug>
#include <QThread>
#include <QAction>
#include <QPushButton>

#include "MoveInterface.h"
#include "GameInterface.h"
#include "IA.h"
#include "RandomAlgorithm.h"
#include "AlgorithmInterface.h"
#include "Human.h"
#include "GameUI.h"
#include "GameController.h"
#include "ModelFactory.h"
#include "Fiar.h"
#include <QBoxLayout>
#include "GameUI.h"
#include "NewGameDialog.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    _menuFile = Q_NULLPTR;
    _newGame = Q_NULLPTR;;
    _startGame = Q_NULLPTR;
    _game = Q_NULLPTR;
    _gameDialog = QSharedPointer<NewGameDialog> ( new NewGameDialog());
    setMinimumSize(800, 600);

    QWidget *centralWidget = new QWidget();
    _hlayout = new QHBoxLayout();
    _hlayout->setAlignment(Qt::AlignTop);
    centralWidget->setLayout(_hlayout);
    setCentralWidget(centralWidget);

    _ui = QSharedPointer<GameUI> (new GameUI(this));
    _controller = QSharedPointer<GameController> (new GameController(this));

    connect(_controller.get(), &GameController::gameChanged, _ui.get(), &GameUI::needToRefresh);
    connect( _ui.get(), &GameUI::newHumanAction, _controller.get(), &GameController::onHumanAction);
    setMenus();
}

MainWindow::~MainWindow()
{

}

void MainWindow::newGame()
{
    //_gameDialog->resetDialog();
    if (_gameDialog->exec() == QDialog::Accepted)
    {
        _controller->clear();
       _game =  _gameDialog->game();
       _controller->setGame(_game);
       _ui->setGame(_game);
       _ui->update();
       QVector<QSharedPointer<PlayerInterface>> players = _gameDialog->players();
       for (int i = 0; i < players.size(); i++)
       {
           players[i]->setConnection(_ui, _controller);
           _controller->addPlayer(players[i]);
       }
       qDebug() << "MainWindow::newGame()  controller->startGame();";
       _controller->startGame();
    }

}


void MainWindow::setMenus()
{
    _menuFile = new QMenu(tr("&File"), this);
    _newGame = new QAction(tr("&New"), this);
    _startGame = new QAction(tr("&Start"), this);
    menuBar()->addMenu(_menuFile);
    _menuFile->addAction(_newGame);
    _menuFile->addAction(_startGame);

    connect(_newGame, &QAction::triggered, this, &MainWindow::newGame);
}

QSharedPointer<GameInterface> MainWindow::game() const
{
    return _game;
}

void MainWindow::setGame(const QSharedPointer<GameInterface> &game)
{
    _game = game;
}
