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
    virtual int eval(int player) override;
    virtual void undo() override;
    virtual bool finish() override;
    virtual int getWinner() override;
    virtual int getMinimumWidth() override;
    virtual int getMinimumHeight() override;
    virtual int getMaxPlayersAllowed() override;
    virtual int getMinPlayersAllowed() override;
    virtual void display(GameUI &ui) override;
    virtual QStringList playerAllowed() override;
    virtual QStringList algorithmAllowedForIa() override ;
    virtual QSharedPointer<GameInterface> clone() override;
    virtual QSharedPointer<MoveInterface> extractMove(QVector<HumanAction> &actions) override;

    static constexpr int COLSIZE = 70;

    virtual void play(FiarMove &move) override;
    virtual bool isLegalMove(FiarMove &move) override;
    int getMoveValue(int row, int col, int player);
    const QVector<QVector<int>> &getBoard();

private:

    QVector<QVector<int>> _board;
    int _winner;
    bool _finished;
    QVector<FiarMove> _history;

private:
    bool isGameFinished(int lastMove);

};

#endif // FOURINAROW_H
