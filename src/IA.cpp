#include "IA.h"

#include "AlgorithmInterface.h"
#include "GameInterface.h"
#include "MoveInterface.h"
#include "GameController.h"

#include <QDebug>

IA::IA()
{

}

IA::IA(QSharedPointer<GameInterface> game, QSharedPointer<AlgorithmInterface> algorithm) :
PlayerInterface(game), _algorithm(algorithm)
{

}

void IA::think()
{
    qDebug() << "IA is thinking...";
    qDebug() << _algorithm.get() << " " << _game.get();
    QSharedPointer<MoveInterface> move = _algorithm->start(_game);
    qDebug() << "IA send move...";
    emit sendMove(move);

}

void IA::setAlgorithm(const QSharedPointer<AlgorithmInterface> &algorithm)
{
    _algorithm = algorithm;
}

void IA::setConnection(QSharedPointer<GameUI> ui, QSharedPointer<GameController> controller)
{
    Q_UNUSED(ui);
    connect(this, &IA::sendMove, controller.get(), &GameController::moveReceived);
}

IA::~IA()
{

}


/*void IA::setGame(QSharedPointer<GameInterface> game)
{
    _game = game;
}*/
