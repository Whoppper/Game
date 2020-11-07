#ifndef MOVEINTERFACE_H
#define MOVEINTERFACE_H

#include "GameInterface.h"


class MoveInterface
{
public:

    //virtual void playInGame(Fiar &fiar) {Q_UNUSED(fiar)};
    virtual void playInGame(QSharedPointer<GameInterface> game) {Q_UNUSED(game)};
    virtual ~MoveInterface() {};

};

#endif // MOVEINTERFACE_H
