#include "IA.h"

#include "AlgorithmInterface.h"
#include "GameInterface.h"
#include "MoveInterface.h"


IA::IA(QSharedPointer<GameInterface> game, QSharedPointer<AlgorithmInterface> algorithm) :
PlayerInterface(game), _algorithm(algorithm)
{

}

QSharedPointer<MoveInterface> IA::getMove()
{
    QSharedPointer<MoveInterface> move = _algorithm->start(_game);
    return move;
}

IA::~IA()
{

}


/*void IA::setGame(QSharedPointer<GameInterface> game)
{
    _game = game;
}*/
