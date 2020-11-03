#include "FiarMove.h"

#include "Fiar.h"

FiarMove::FiarMove()
{

}

FiarMove::FiarMove(int col) : _col(col)
{

}

void FiarMove::playInGame(Fiar &fiar)
{
    fiar.play(*this);
}

int FiarMove::col() const
{
    return _col;
}

void FiarMove::setCol(int col)
{
    _col = col;
}
