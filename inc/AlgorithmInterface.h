#ifndef ALGORITHMINTERFACE_H
#define ALGORITHMINTERFACE_H

#include <QSharedPointer>


class GameInterface;
class MoveInterface;

class AlgorithmInterface
{
public:

    virtual QSharedPointer<MoveInterface> start(QSharedPointer<GameInterface> game) = 0;

};





#endif // ALGORITHMINTERFACE_H
