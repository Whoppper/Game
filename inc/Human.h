#ifndef HUMAN_H
#define HUMAN_H

#include "PlayerInterface.h"
#include <QSharedPointer>
#include <QPoint>
#include "HumanAction.h"

class GameInterface;
class MoveInterface;

class Human : public PlayerInterface
{
    Q_OBJECT
public:

    Human();
    Human(QSharedPointer<GameInterface> game);
    virtual void think() override;
    virtual void setConnection(QSharedPointer<GameUI> ui, QSharedPointer<GameController> controller) override;
    virtual void parseUserInput(HumanAction action) override;

private:

    bool _needToPlay;
    QVector<HumanAction> _actions; // QVector si l'human doit faire plusieurs clicks pour jouer un move
};

#endif // HUMAN_H
