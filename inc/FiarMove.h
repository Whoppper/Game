#ifndef FIARMOVE_H
#define FIARMOVE_H

#include "MoveInterface.h"

class GameInterface;

class FiarMove : public MoveInterface
{
public:
    FiarMove();
    FiarMove(int col);
    virtual ~FiarMove();
    virtual void playInGame(QSharedPointer<GameInterface> game) override;
    virtual bool isValidMove(QSharedPointer<GameInterface> game) override;
    int col() const;
    void setCol(int col);
    virtual QString toString() override
    {
        return QString("col: %1  ").arg(QString::number(_col));
    }

private:
    int _col;
};

#endif // FIARMOVE_H
