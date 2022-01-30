#ifndef MINMAXALGORITHM_H
#define MINMAXALGORITHM_H

#include "AlgorithmInterface.h"
#include <QSharedPointer>

class MoveInterface;
class GameInterface;

class MinMaxAlgorithm : public AlgorithmInterface
{
    Q_OBJECT
public:
    MinMaxAlgorithm(double timeAllowed);
    virtual ~MinMaxAlgorithm();
    virtual void start() override;

    int alphabeta(QSharedPointer<GameInterface> &game, int alpha, int beta, int depth, int actualDepth, QVector<QSharedPointer<MoveInterface>> &principaleVariationTmp, int nodeType);

private:
    QVector<QSharedPointer<MoveInterface>> _principaleVariation;
    int _playerNumber;
    int _visitedState;
};

#endif // MINMAXALGORITHM_H
