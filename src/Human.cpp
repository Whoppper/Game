#include "Human.h"

#include "GameInterface.h"
#include "MoveInterface.h"
#include "GameController.h"
#include "GameUI.h"
#include <QDebug>

Human::Human(QSharedPointer<GameInterface> game) : PlayerInterface(game), _needToPlay(false)
{
}

Human::Human() : _needToPlay(false)
{
}

void Human::think()
{
    _needToPlay = true;
}

void Human::parseUserInput(HumanAction action)
{
    if (!_needToPlay) // si c'est pas au tour du joueur
        return;
    _actions.push_back(action);
    QSharedPointer<MoveInterface> newMove = _game->extractMove(_actions); // _game can remove some action in _actions
    if (newMove != Q_NULLPTR && newMove->isValidMove(_game))
    {
        _needToPlay = false;
        _actions.clear();
        emit sendMove(newMove);
    }
}

void Human::setConnection(QSharedPointer<GameUI> ui, QSharedPointer<GameController> controller)
{
    Q_UNUSED(ui);
    connect(this, &Human::sendMove, controller.get(), &GameController::moveReceived);
}
