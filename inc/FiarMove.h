#ifndef FIARMOVE_H
#define FIARMOVE_H

#include "MoveInterface.h"

class GameInterface;

class FiarMove : public MoveInterface
{
public:
    FiarMove();
    FiarMove(int col);

    //virtual void playInGame(Fiar &fiar) override;
    virtual void playInGame(QSharedPointer<GameInterface> game) override;
    int col() const;
    void setCol(int col);

private:
    int _col;
};


#endif // FIARMOVE_H
