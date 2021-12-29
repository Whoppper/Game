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
class UtttMove;
class MoveInterface;
class GameUI;

class GameInterface
{
public:

    virtual QVector<QSharedPointer<MoveInterface>> getMoves() = 0;
    virtual int eval(int player) = 0;
    virtual void undo() = 0;
    virtual int getWinner() = 0;
    virtual bool finish() = 0;
    virtual void display(GameUI &ui) = 0;
    virtual int getMaxPlayersAllowed() = 0;
    virtual int getMinPlayersAllowed() = 0;
    virtual int getMinimumHeight() = 0;
    virtual int getMinimumWidth() = 0;
    virtual QStringList playerAllowed() {return {};};
    virtual QStringList algorithmAllowedForIa() {return {};}
    virtual QSharedPointer<MoveInterface> extractMove(QVector<HumanAction> &actions) = 0;
    virtual QSharedPointer<GameInterface> clone() = 0;

    virtual void play(FiarMove &move) {Q_UNUSED(move)};
    virtual bool isLegalMove(FiarMove &move) {Q_UNUSED(move);return false;};

    virtual void play(UtttMove &move) {Q_UNUSED(move)};
    virtual bool isLegalMove(UtttMove &move) {Q_UNUSED(move);return false;};


    int playerTurn() const {return _playerTurn;}
    void setPlayerTurn(int newPlayerTurn){_playerTurn = newPlayerTurn;}

protected:
    int _playerTurn;
};

#endif // GAME_H
