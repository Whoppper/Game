#ifndef GAME_H
#define GAME_H

#include <QVector>
#include <QPair>
#include <QSharedPointer>
#include "HumanAction.h"

constexpr int PLAYER_1 = 1;
constexpr int PLAYER_2 = 2;
constexpr int DRAW = 0;

class FiarMove;
class MoveInterface;
class GameUI;

class GameInterface
{
public:

    virtual QVector<QSharedPointer<MoveInterface>> getMoves() = 0;
    virtual int eval() = 0;
    virtual void undo() = 0;
    virtual int getWinner() = 0;
    virtual bool finish() = 0;
    virtual void display(GameUI &ui) = 0;
    virtual int getMinimumWidth() = 0;
    virtual int getMinimumHeight() = 0;
    virtual int playerTurn() = 0;
    virtual QSharedPointer<MoveInterface> extractMove(QVector<HumanAction> &actions) = 0;
    virtual QSharedPointer<GameInterface> clone() = 0;

    // beurk(to avoid dynamic cast)
    virtual void play(FiarMove &move) {Q_UNUSED(move)};
    virtual bool isLegalMove(FiarMove &move) {Q_UNUSED(move);return false;};
};

#endif // GAME_H
