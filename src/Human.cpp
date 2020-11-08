#include "Human.h"

#include "GameInterface.h"
#include "MoveInterface.h"

#include <QDebug>


Human::Human(QSharedPointer<GameInterface> game) : PlayerInterface(game), _needToPlay(false)
{

}

void Human::think()
{
    qDebug() << "Human::think()";
    _needToPlay = true;
}

void Human::onHumanPlay(HumanAction action)
{
    qDebug() << "Human::onHumanPlay";
    if (!_needToPlay) // si c'est pas au tour du joueur
        return ;
    qDebug() << "Human::onHumanPlay needtoplay is true";
    _actions.push_back(action);
    QSharedPointer<MoveInterface> newMove = _game->extractMove(_actions); // game can remove some action in _actions
    if (newMove != Q_NULLPTR && newMove->isValidMove(_game))
    {
        // game->move() ?

        qDebug() << "HUMAN SEND MOVE";
        _needToPlay = false;
        _actions.clear();
        emit sendMove(newMove);

    }
}
