#ifndef MOVEINTERFACE_H
#define MOVEINTERFACE_H

#include "GameInterface.h"

class Fiar;

class MoveInterface
{
public:

    virtual void playInGame(Fiar &fiar) {Q_UNUSED(fiar)};

    virtual ~MoveInterface() {};

};

#endif // MOVEINTERFACE_H
