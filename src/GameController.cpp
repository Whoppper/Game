#include "GameController.h"

GameController::GameController(QObject *parent) : QObject(parent)
{

}

void GameController::addPlayer(QSharedPointer<PlayerInterface> player)
{
    _players.push_back(player);
}
