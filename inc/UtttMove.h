#ifndef UTTTMOVE_H
#define UTTTMOVE_H

#include "MoveInterface.h"

class GameInterface;

class UtttMove : public MoveInterface
{
public:
    UtttMove();
    UtttMove(int row, int col);
    virtual ~UtttMove();
    virtual void playInGame(QSharedPointer<GameInterface> game) override;
    virtual bool isValidMove(QSharedPointer<GameInterface> game) override;
    int col() const;
    int row() const;
    void setCol(int col);
    void setRow(int row);
    virtual QString toString() override
    {
        return QString("row: %1 , col: %2  ").arg(QString::number(_row)).arg(QString::number(_col));
    }

private:
    int _row;
    int _col;
};

#endif // FIARMOVE_H
