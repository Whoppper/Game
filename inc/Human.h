#ifndef HUMAN_H
#define HUMAN_H

#include "PlayerInterface.h"
#include <QSharedPointer>

class GameInterface;
class MoveInterface;

class Human : public PlayerInterface
{
public:

    Human(QSharedPointer<GameInterface> game);

    virtual QSharedPointer<MoveInterface> getMove();


};

#endif // HUMAN_H
