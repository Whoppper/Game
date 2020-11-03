#ifndef PLAYERINTERFACE_H
#define PLAYERINTERFACE_H

#include <QSharedPointer>

class GameInterface;
class MoveInterface;

class PlayerInterface
{
public:
    PlayerInterface(QSharedPointer<GameInterface> game) : _game(game) {};
    virtual QSharedPointer<MoveInterface> getMove() = 0;


protected:
    QSharedPointer<GameInterface> _game;

};


#endif // PLAYERINTERFACE_H
