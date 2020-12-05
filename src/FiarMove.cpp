#include "FiarMove.h"

#include "Fiar.h"
#include "GameInterface.h"

FiarMove::FiarMove()
{

}

FiarMove::FiarMove(int col) : _col(col)
{

}
FiarMove::~FiarMove()
{

}

bool FiarMove::isValidMove(QSharedPointer<GameInterface> game)
{
    return game->isLegalMove(*this);
}

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
