#ifndef GAME_H
#define GAME_H

#include <QVector>
#include <QPair>
#include <QSharedPointer>

constexpr int PLAYER_1 = 1;
constexpr int PLAYER_2 = 2;
constexpr int DRAW = 0;

class FiarMove;
class MoveInterface;

class GameInterface
{
public:

    virtual QVector<QSharedPointer<MoveInterface>> getMoves() = 0;
    virtual int eval() = 0;
    virtual void undo() = 0;
    virtual int getWinner() = 0;

    virtual void play(FiarMove &move) {Q_UNUSED(move)};
};

#endif // GAME_H
