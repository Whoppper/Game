#include "UtttMove.h"

#include "Uttt.h"
#include "GameInterface.h"

UtttMove::UtttMove()
{

}

UtttMove::UtttMove(int row, int col) : _row(row), _col(col)
{

}
UtttMove::~UtttMove()
{

}

bool UtttMove::isValidMove(QSharedPointer<GameInterface> game)
{
    return game->isLegalMove(*this);
}

void UtttMove::playInGame(QSharedPointer<GameInterface> game)
{
    game->play(*this);
}

int UtttMove::col() const
{
    return _col;
}

void UtttMove::setCol(int col)
{
    _col = col;
}

int UtttMove::row() const
{
    return _row;
}

void UtttMove::setRow(int row)
{
    _row = row;
}

