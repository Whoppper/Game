#include "FiarMove.h"

#include "Fiar.h"
#include "GameInterface.h"

FiarMove::FiarMove()
{

}

FiarMove::FiarMove(int col) : _col(col)
{

}

/*void FiarMove::playInGame(Fiar &fiar)
{
    fiar.play(*this);
}*/

void FiarMove::playInGame(QSharedPointer<GameInterface> game)
{
    game->play(*this);
}

int FiarMove::col() const
{
    return _col;
}

void FiarMove::setCol(int col)
{
    _col = col;
}
