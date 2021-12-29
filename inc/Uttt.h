#ifndef UTTT_H
#define UTTT_H

#include "GameInterface.h"

class GameUI;
class MoveInterface;

class Uttt : public GameInterface
{
public:

    Uttt();
    virtual ~Uttt();

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
    virtual void play(UtttMove &move) override;
    virtual bool isLegalMove(UtttMove &move) override;
     bool isLegal(int row, int col);

    const QVector<QVector<QVector<int> > > &boards() const;
    void setBoards(const QVector<QVector<QVector<int> > > &newBoards);

    const QVector<QVector<int> > &board() const;
    void setBoard(const QVector<QVector<int> > &newBoard);

private:

    QVector<QVector<QVector<int>>> _boards;
    QVector<QVector<int>> _board;
    int _winner;
    bool _finished;
    int _nextboard;


private:


};

#endif // FOURINAROW_H
