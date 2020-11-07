#ifndef PLAYERINTERFACE_H
#define PLAYERINTERFACE_H

#include <QSharedPointer>

#include "GameInterface.h"
class MoveInterface;

class PlayerInterface
{
public:
    PlayerInterface(const QSharedPointer<GameInterface> game) : _game(game) {};
    virtual QSharedPointer<MoveInterface> getMove() = 0;
    void setGame(QSharedPointer<GameInterface> game) {_game = game;}


protected:
    QSharedPointer<GameInterface> _game;

};


#endif // PLAYERINTERFACE_H
