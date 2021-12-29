#include "Uttt.h"

#include "ModelFactory.h"
#include "MoveInterface.h"
#include "UtttMove.h"
#include "GameUI.h"
#include <QDebug>
#include <QPoint>

namespace
{
    void getCoordFromPosition(QPoint position, QPair<int, int> &coord)
    {
        coord.first = position.y() / 60;
        coord.second = position.x() / 60;
    }

    int checkResult(QVector<QVector<int>> &board, int playerTurn)
    {
        if ((board[0][0] == board[0][1] && board[0][0] == board[0][2] && board[0][0] > 0) ||
            (board[1][0] == board[1][1] && board[1][0] == board[1][2] && board[1][0] > 0) ||
            (board[2][0] == board[2][1] && board[2][0] == board[2][2] && board[2][0] > 0) ||
            (board[0][0] == board[1][0] && board[0][0] == board[2][0] && board[0][0] > 0) ||
            (board[0][1] == board[1][1] && board[0][1] == board[2][1] && board[0][1] > 0) ||
            (board[0][2] == board[1][2] && board[0][2] == board[2][2] && board[0][2] > 0) ||
            (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] > 0) ||
            (board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[0][2] > 0)
            )
        {
            return playerTurn;
        }
        for (int row = 0; row < 3 ; row++)
        {
            for (int col = 0; col < 3 ; col++)
            {
                if (board[row][col] == -1)
                {
                    return -1;
                }
            }
        }
        return 0;
    }
}

Uttt::Uttt() :
    _boards(9, QVector<QVector<int>>(3, QVector<int>(3, -1))) ,
    _board(3, QVector<int>(3, -1)) ,
    _winner(-1) ,
    _finished(false),
    _nextboard(-1)
{
    _playerTurn = PLAYER_1;
}

Uttt::~Uttt()
{

}

int Uttt::getMinimumWidth()
{
    return 9 * 60;
}
int Uttt::getMinimumHeight()
{
    return 9 * 60;
}

void Uttt::display(GameUI &ui)
{
    ui.displayGame(*this);
}

bool Uttt::finish()
{
    return _finished;
}


QStringList Uttt::playerAllowed()
{
    return {"None", "IA", "Human"};
}


QStringList Uttt::algorithmAllowedForIa()
{
    return {"Random", "MinMax", "Mcts"};
}

QSharedPointer<MoveInterface> Uttt::extractMove(QVector<HumanAction> &actions)
{
    for (int i = 0; i < actions.size(); i++)
    {
        if (actions[i].action == ActionType::MouseClick)
        {
            QSharedPointer<UtttMove> move = ModelFactory::create<UtttMove>();
            QPair<int, int> coord;
            getCoordFromPosition(actions[i].position, coord);
            move->setCol(coord.second);
            move->setRow(coord.first);
            actions.clear();
            return move;
        }
    }
    actions.clear();
    return Q_NULLPTR;
}

bool Uttt::isLegalMove(UtttMove &move)
{
    int col = move.col();
    int row = move.row();
    if (_finished || col > 8 || row > 8 || col < 0 || row < 0)
        return false;
    int utttrow = (row / 3);
    int utttcol = (col / 3 );
    int tttrow = (row % 3);
    int tttcol = (col % 3 );
    int boardIndex = (row / 3) * 3 + col / 3;
    if (boardIndex == _nextboard || (_nextboard == -1 && _board[utttrow ][utttcol ] == -1))
    {
        if (_boards[boardIndex][tttrow][tttcol] != -1)
        {
             return false;
        }
        return true;
    }
    else
    {
        return false;
    }
    return true;
}

bool Uttt::isLegal(int row, int col)
{
    if (_finished || col > 8 || row > 8 || col < 0 || row < 0)
        return false;
    int utttrow = (row / 3);
    int utttcol = (col / 3 );
    int tttrow = (row % 3);
    int tttcol = (col % 3 );
    int boardIndex = (row / 3) * 3 + col / 3;
    if (boardIndex == _nextboard || (_nextboard == -1 && _board[utttrow ][utttcol ] == -1))
    {
        if (_boards[boardIndex][tttrow][tttcol] != -1)
        {
             return false;
        }
        return true;
    }
    else
    {
        return false;
    }
    return true;
}

const QVector<QVector<QVector<int> > > &Uttt::boards() const
{
    return _boards;
}

void Uttt::setBoards(const QVector<QVector<QVector<int> > > &newBoards)
{
    _boards = newBoards;
}

const QVector<QVector<int> > &Uttt::board() const
{
    return _board;
}

void Uttt::setBoard(const QVector<QVector<int> > &newBoard)
{
    _board = newBoard;
}

QVector<QSharedPointer<MoveInterface>> Uttt::getMoves()
{
    QVector<QSharedPointer<MoveInterface>> moves;
    if (_finished)
        return moves;
    if (_nextboard == -1)
    {
        for (int i = 0; i < _boards.size() ; i++)
        {
            int utttrow = (i / 3);
            int utttcol = (i % 3 );
            if (_board[utttrow][utttcol] != -1)
                continue;
            for (int row = 0; row < 3 ; row++)
            {
                for (int col = 0; col < 3 ; col++)
                {
                    if (_boards[i][row][col] == -1)
                    {
                        QSharedPointer<UtttMove> move = ModelFactory::create<UtttMove>();
                        move->setRow(utttrow * 3 + row);
                        move->setCol(utttcol * 3 + col);
                        moves.push_back(move);
                    }
                }
            }
        }
    }
    else
    {
        int utttrow = (_nextboard / 3);
        int utttcol = (_nextboard % 3 );
        for (int row = 0; row < 3 ; row++)
        {
            for (int col = 0; col < 3 ; col++)
            {
                if (_boards[_nextboard][row][col] == -1)
                {
                    QSharedPointer<UtttMove> move = ModelFactory::create<UtttMove>();
                    move->setRow(utttrow * 3 + row);
                    move->setCol(utttcol * 3 + col);
                    moves.push_back(move);
                }
            }
        }
    }
    return moves;
}

int Uttt::getMaxPlayersAllowed()
{
    return 2;
}
int Uttt::getMinPlayersAllowed()
{
    return 2;
}

int Uttt::eval(int player)
{
    return 1;
}

void Uttt::play(UtttMove &move)
{
    if (_finished)
        return ;
    int col = move.col();
    int row = move.row();
    int utttrow = (row / 3);
    int utttcol = (col / 3 );
    int tttrow = (row % 3);
    int tttcol = (col % 3 );

    if (!isLegalMove(move))
    {
        qWarning() << "invalid move " << row <<" " << col ;

        return ;
    }
    _boards[utttrow * 3 + utttcol][tttrow][tttcol] = _playerTurn;
    _nextboard = tttrow * 3 + tttcol;
    if (checkResult (_boards[_nextboard], _playerTurn) > -1)
    {
        _nextboard = -1;
    }
    int result = checkResult(_boards[utttrow * 3 + utttcol], _playerTurn);
    if (result > -1)
    {
        _board[utttrow][utttcol] = result;
        if (checkResult(_board, _playerTurn) > -1)
        {
            _finished = true;
            _winner = checkResult(_board, _playerTurn);
        }

    }

    _playerTurn = 3 - _playerTurn;
}

void Uttt::undo()
{
    /*if (_history.size() == 0)
        return ;
    _finished = false;
    _winner = -1;
    _playerTurn = 3 - _playerTurn;
    int col = _history[_history.size() -1].col();
    _history.pop_back();
    int i = 0;
    while (i < BOARD_HEIGHT && _board[i][col] != _playerTurn)
    {
        i++;
    }
    if (i == BOARD_HEIGHT)
    {
        qWarning() << "undo problem " << col;
        return ;
    }
    _board[i][col] = 0;*/
}

int Uttt::getWinner()
{
    if (!_finished)
        return -1;
    return _winner;
}

QSharedPointer<GameInterface> Uttt::clone()
{

    Uttt *uttt = new Uttt();
    uttt->_playerTurn = _playerTurn;
    uttt->_finished = _finished;
    uttt->_board = _board;
    uttt->_boards = _boards;
    uttt->_winner = _winner;
    uttt->_nextboard = _nextboard;

    QSharedPointer<GameInterface> cpy(uttt);
    return cpy;
}


