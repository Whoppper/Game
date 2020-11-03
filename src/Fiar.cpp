#include "Fiar.h"

#include "ModelFactory.h"
#include "MoveInterface.h"
#include "FiarMove.h"

Fiar::Fiar() :
    _board(BOARD_HEIGHT, QVector<int>(BOARD_WIDTH, 0)) ,
    _winner(-1) ,
    _finished(false) ,
    _playerTurn(PLAYER_1)
{

}


QVector<QSharedPointer<MoveInterface>> Fiar::getMoves()
{
    QVector<QSharedPointer<MoveInterface>> moves;
    if (_finished)
        return moves;
    for (int i = 0; i < BOARD_WIDTH; i++)
    {
        if (_board[0][i] == 0)
        {
            QSharedPointer<MoveInterface> move = ModelFactory::create<FiarMove>();
            moves.push_back(move);
        }
    }
    return moves;
}

int Fiar::eval()
{
    // TODO
    return 1;
}

void Fiar::play(FiarMove &move)
{

}

void Fiar::undo()
{

}

int Fiar::getWinner()
{

}
