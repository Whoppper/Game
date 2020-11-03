#ifndef FOURINAROW_H
#define FOURINAROW_H

#include "GameInterface.h"

constexpr int BOARD_WIDTH = 7;
constexpr int BOARD_HEIGHT = 6;

class Fiar : public GameInterface
{
public:

    Fiar();

    virtual QVector<QSharedPointer<MoveInterface>> getMoves() override;
    virtual int eval() override;
    virtual void play(FiarMove &move) override;
    virtual void undo() override;
    virtual int getWinner() override;

private:

    QVector<QVector<int>> _board;
    int _winner;
    bool _finished;
    QVector<QSharedPointer<MoveInterface>> _history;
    int _playerTurn;

};

#endif // FOURINAROW_H
