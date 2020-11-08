#include "GameController.h"

#include "PlayerInterface.h"
#include "GameInterface.h"
#include "MoveInterface.h"
#include <QDebug>

// TODO CHANGER LE PLAYER TURN

GameController::GameController(QObject *parent) : QObject(parent), _gameInProgress(false)
{

}

void GameController::addPlayer(QSharedPointer<PlayerInterface> player)
{
    if (!_gameInProgress)
    {
        _players.push_back(player);
        player->setPlayerNum(_players.size());
    }
}

void GameController::setGame(QSharedPointer<GameInterface> game)
{
    if (!_gameInProgress)
    {
        _game = game;
    }
}

void GameController::startGame()
{
    _gameInProgress = true;

    _players[0]->setGame(_game->clone());
    _players[0]->think();
}

void GameController::moveReceived(QSharedPointer<MoveInterface> move)
{
    qDebug() << "moveReceived;";
    if (!_gameInProgress || move == Q_NULLPTR)
    {
        return ;
    }
   PlayerInterface * player = qobject_cast<PlayerInterface *>(sender());
   if( player != Q_NULLPTR )
   {
        if (_game->playerTurn() == player->PlayerNum() && move->isValidMove(_game))
        {
            move->playInGame(_game);
            emit gameChanged();
            if (_game->finish())
            {
                _gameInProgress = false;
                qDebug() << "winner: " << _game->getWinner();
                return ;
            }
            int playerTurn = _game->playerTurn() -1;
            if (playerTurn < _players.size())
            {
                // TODO for each player (online mode) avec le signal gameChanged
                _players[playerTurn]->setGame(_game->clone());
                //

                qDebug() << "player: " << playerTurn << " is thinking";
                _players[playerTurn]->think();
            }
            else
                qWarning() << "GameController::moveReceived error player turn;";
        }
   }
}
