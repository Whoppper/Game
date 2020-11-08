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
    Q_OBJECT
public:

    virtual ~IA();
    IA(QSharedPointer<GameInterface> game, QSharedPointer<AlgorithmInterface> algorithm);

    virtual void think() override;

signals:
    void sendMove(QSharedPointer<MoveInterface> move);



private:
    QThread *_thread;
    QSharedPointer<AlgorithmInterface> _algorithm;

};



#endif // IA_H
