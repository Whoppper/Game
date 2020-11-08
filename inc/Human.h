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

    Human(QSharedPointer<GameInterface> game);

    virtual void think() override;

public slots:
    void onHumanPlay(HumanAction action);

// inhe   signal  sendMove(QSharedPointer<MoveInterface> move);
signals:
    void sendMove(QSharedPointer<MoveInterface> move);
private:

    // inhe QSharedPointer<GameInterface> _game;
    // inhe int _playerNum;


    bool _needToPlay;
    QVector<HumanAction> _actions; // QVector si l'human doit faire plusieurs clicks pour jouer un move
};

#endif // HUMAN_H
