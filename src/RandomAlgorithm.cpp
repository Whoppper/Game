#include "RandomAlgorithm.h"

#include "GameInterface.h"
#include "MoveInterface.h"
#include <QRandomGenerator>

QSharedPointer<MoveInterface> start(GameInterface *game /* timeAllowed   */)
{
    QVector<QSharedPointer<MoveInterface>> moves = game->getMoves();
    int randMove = QRandomGenerator::global()->generate() % moves.size();
    return moves[randMove];
}
