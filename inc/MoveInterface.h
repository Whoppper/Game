#ifndef MOVEINTERFACE_H
#define MOVEINTERFACE_H

#include "GameInterface.h"

class MoveInterface
{
public:
    virtual void playInGame(QSharedPointer<GameInterface> game) { Q_UNUSED(game) };
    virtual bool isValidMove(QSharedPointer<GameInterface> game)
    {
        Q_UNUSED(game);
        return false;
    };
    virtual QString toString()
    {
        return "";
    };
    virtual ~MoveInterface(){};
};

typedef QSharedPointer<MoveInterface> MovePtr;

#endif // MOVEINTERFACE_H
