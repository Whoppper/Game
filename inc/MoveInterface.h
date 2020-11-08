#ifndef MOVEINTERFACE_H
#define MOVEINTERFACE_H

#include "GameInterface.h"


class MoveInterface
{
public:

    virtual void playInGame(QSharedPointer<GameInterface> game) {Q_UNUSED(game)}; // =0 ?
    virtual bool isValidMove(QSharedPointer<GameInterface> game) {Q_UNUSED(game);return false;};// =0 ?
    virtual ~MoveInterface() {};

};

#endif // MOVEINTERFACE_H
