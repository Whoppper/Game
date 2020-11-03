#include "Human.h"

#include "GameInterface.h"
#include "MoveInterface.h"

Human::Human(QSharedPointer<GameInterface> game) : PlayerInterface(game)
{

}

QSharedPointer<MoveInterface> Human::getMove()
{
    //game.getHumanMove
}
