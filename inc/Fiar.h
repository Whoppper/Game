#ifndef FOURINAROW_H
#define FOURINAROW_H

#include "GameInterface.h"

constexpr int BOARD_WIDTH = 7;
constexpr int BOARD_HEIGHT = 6;

class GameUI;
class MoveInterface;

class Fiar : public GameInterface
{
public:

    Fiar();
    virtual ~Fiar();

    virtual QVector<QSharedPointer<MoveInterface>> getMoves() override;
    virtual int eval() override;
    virtual void play(FiarMove &move) override;
    virtual void undo() override;
    virtual bool finish() override;
    virtual int getWinner() override;
    virtual void display(GameUI &ui) override;
    virtual QSharedPointer<GameInterface> clone() override;

    const QVector<QVector<int>> &getBoard();

private:

    QVector<QVector<int>> _board;
    int _winner;
    bool _finished;
    QVector<FiarMove> _history;
    int _playerTurn;

private:
    bool isGameFinished(int lastMove);

};

#endif // FOURINAROW_H
