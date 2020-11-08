#include "IA.h"

#include "AlgorithmInterface.h"
#include "GameInterface.h"
#include "MoveInterface.h"

#include <QDebug>


IA::IA(QSharedPointer<GameInterface> game, QSharedPointer<AlgorithmInterface> algorithm) :
PlayerInterface(game), _algorithm(algorithm)
{

}

void IA::think()
{
    qDebug() << "IA::think()";
    QSharedPointer<MoveInterface> move = _algorithm->start(_game);
    emit sendMove(move);
}

IA::~IA()
{

}


/*void IA::setGame(QSharedPointer<GameInterface> game)
{
    _game = game;
}*/
