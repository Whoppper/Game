#ifndef IA_H
#define IA_H

#include "PlayerInterface.h"
#include <QSharedPointer>
#include <QThread>

class GameInterface;
class MoveInterface;
class AlgorithmInterface;

class IA : public PlayerInterface
{
public:

    virtual ~IA();
    IA(QSharedPointer<GameInterface> game, QSharedPointer<AlgorithmInterface> algorithm);

    virtual QSharedPointer<MoveInterface> getMove();
    //void setGame(QSharedPointer<GameInterface> game);

private:
    QThread *_thread;
    QSharedPointer<AlgorithmInterface> _algorithm;

};



#endif // IA_H
