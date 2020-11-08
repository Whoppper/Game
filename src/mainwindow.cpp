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

#include <QThread>
#include <QPushButton>

#include "GameUI.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setMinimumSize(800, 600);
    QWidget *centralWidget = new QWidget(); // no delete needed
    QHBoxLayout *hlayout = new QHBoxLayout(); // no delete needed
    hlayout->setAlignment(Qt::AlignTop);
    centralWidget->setLayout(hlayout);
    setCentralWidget(centralWidget);

    _game= ModelFactory::create<Fiar>();
    _ui = new GameUI(this, _game); // no delete needed

    _controller = new GameController(this);
    QSharedPointer<AlgorithmInterface> algop1 = ModelFactory::create<RandomAlgorithm>();
    Human *human = new Human(_game->clone());
    IA *ia = new IA(_game->clone(), algop1);
    QSharedPointer<PlayerInterface> p1 (ia);
    QSharedPointer<PlayerInterface> p2 (human);
    _controller->addPlayer(p1);
    _controller->addPlayer(p2);
    _controller->setGame(_game);

    connect(_ui, &GameUI::newHumanAction, human, &Human::onHumanPlay);
    connect(_controller, &GameController::gameChanged, _ui, &GameUI::needToRefresh);
    connect(ia, &IA::sendMove, _controller, &GameController::moveReceived );
    connect(human, &Human::sendMove, _controller, &GameController::moveReceived );

    QPushButton *_button = new QPushButton("GO", this); // no delete needed
    hlayout->addWidget(_ui);
    hlayout->addWidget(_button);
    connect(_button, &QPushButton::clicked, this, &MainWindow::startGame);
}

void MainWindow::startGame(int)
{
    _controller->startGame();
}

MainWindow::~MainWindow()
{
    
}

