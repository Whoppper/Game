#include "RandomAlgorithm.h"

#include "GameInterface.h"
#include "MoveInterface.h"
#include <QRandomGenerator>
#include <QDebug>


QSharedPointer<MoveInterface> RandomAlgorithm::start()
{
    qRegisterMetaType<MovePtr>("MovePtr");
    QVector<QSharedPointer<MoveInterface>> moves = _game->getMoves();
    if (moves.size() == 0)
    {
        qDebug() << "Error move.size == 0";

    }
    //int randMove = QRandomGenerator::global()->generate() % moves.size();
    int randMove = rand() % moves.size();
    emit resultReady(moves[randMove]);
    return moves[randMove];
}

RandomAlgorithm::RandomAlgorithm()
{

}


RandomAlgorithm::~RandomAlgorithm()
{

}
