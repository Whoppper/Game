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
    RandomAlgorithm(double timeAllowed);
    virtual ~RandomAlgorithm();
    virtual void start() override;
};

#endif // RANDOMALGORITHM_H
