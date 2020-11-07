#ifndef RANDOMALGORITHM_H
#define RANDOMALGORITHM_H

#include "AlgorithmInterface.h"
#include <QSharedPointer>

class MoveInterface;
class GameInterface;

class RandomAlgorithm : public AlgorithmInterface
{
public:

    virtual ~RandomAlgorithm();
    virtual QSharedPointer<MoveInterface> start(QSharedPointer<GameInterface> game /* + timeAllowed from ia  */) override;
};





#endif // RANDOMALGORITHM_H
