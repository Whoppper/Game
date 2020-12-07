#include "GameController.h"

#include "PlayerInterface.h"
#include "GameInterface.h"
#include "MoveInterface.h"
#include <QDebug>

// TODO CHANGER LE PLAYER TURN

GameController::GameController(QObject *parent) : QObject(parent), _gameInProgress(false), _playerTurn(1)
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

void GameController::clear()
{
    _gameInProgress = false;
    _players.clear();
   // if (_game != Q_NULLPTR)
        _game.reset();
    _playerTurn = 1;
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
    qDebug() << "GameController::startGame()" << _players.size();
    if (_players.size() > 0)
    {
        _gameInProgress = true;
        _players[0]->setGame(_game->clone());
        _players[0]->think();
    }
}

void GameController::onHumanAction(HumanAction action)
{
    if (!_gameInProgress)
    {
        return ;
    }
    int indexActualPlayer = _playerTurn - 1;
    _players[indexActualPlayer]->parseUserInput(action);
}

void GameController::moveReceived(QSharedPointer<MoveInterface> move)
{
    qDebug() << "moveReceived;";
    if (!_gameInProgress || move == Q_NULLPTR)
    {
        return ;
    }
    int indexActualPlayer = _playerTurn - 1;
    PlayerInterface * player = qobject_cast<PlayerInterface *>(sender());
    if( player != Q_NULLPTR )
    {
        if (_players[indexActualPlayer] == player && move->isValidMove(_game))
        {
            qDebug() << "emit gameChanged();";
            move->playInGame(_game);
            emit gameChanged();
            if (_game->finish())
            {
                _gameInProgress = false;
                qDebug() << "winner: " << _game->getWinner();
                return ;
            }
           _playerTurn = _playerTurn + 1 > _players.size() ? 1 : _playerTurn + 1;
           indexActualPlayer = _playerTurn - 1;
            if (indexActualPlayer < _players.size())
            {
                // TODO pour chaque player avec le signal gameChanged
                _players[indexActualPlayer]->setGame(_game->clone());
                //

                qDebug() << "player: " << _playerTurn << " is thinking";
                _players[indexActualPlayer]->think();
            }
            else
                qWarning() << "GameController::moveReceived error player turn;";
        }
   }
}
