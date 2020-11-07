#include "RandomAlgorithm.h"

#include "GameInterface.h"
#include "MoveInterface.h"
#include <QRandomGenerator>
#include <QDebug>
QSharedPointer<MoveInterface> RandomAlgorithm::start(QSharedPointer<GameInterface> game  /* timeAllowed   */)
{
    QVector<QSharedPointer<MoveInterface>> moves = game->getMoves();
    if (moves.size() == 0)
    {
        qDebug() << "Error move.size == 0";

    }
    //int randMove = QRandomGenerator::global()->generate() % moves.size();
    int randMove = rand() % moves.size();
    return moves[randMove];
}


RandomAlgorithm::~RandomAlgorithm()
{

}
