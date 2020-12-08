#ifndef RANDOMALGORITHM_H
#define RANDOMALGORITHM_H

#include "AlgorithmInterface.h"
#include <QSharedPointer>

class MoveInterface;
class GameInterface;

class RandomAlgorithm : public AlgorithmInterface
{
    Q_OBJECT
public:
    RandomAlgorithm();
    virtual ~RandomAlgorithm();
    virtual QSharedPointer<MoveInterface> start() override;

//signals:
//    void resultReady(QSharedPointer<MoveInterface> move);
};





#endif // RANDOMALGORITHM_H
