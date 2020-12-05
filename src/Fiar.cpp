#include "Fiar.h"

#include "ModelFactory.h"
#include "MoveInterface.h"
#include "FiarMove.h"
#include "GameUI.h"

#include <QDebug>
#include <QPoint>

namespace
{
    int getColumnFromPosition(QPoint position)
    {
        int col = position.x() / 70;
        return col;
    }
}

Fiar::Fiar() :
    _board(BOARD_HEIGHT, QVector<int>(BOARD_WIDTH, 0)) ,
    _winner(-1) ,
    _finished(false) ,
    _playerTurn(PLAYER_1)
{

}

Fiar::~Fiar()
{

}

int Fiar::getMinimumWidth()
{
    return BOARD_WIDTH * 70;
}
int Fiar::getMinimumHeight()
{
    return BOARD_HEIGHT * 70;
}

void Fiar::display(GameUI &ui)
{
    ui.displayGame(*this);
}

bool Fiar::finish()
{
    return _finished;
}

const QVector<QVector<int>> &Fiar::getBoard()
{
    return _board;
}

QStringList Fiar::playerAllowed()
{
    return {"None", "IA", "Human"};
}


QStringList Fiar::algorithmAllowedForIa()
{
    return {"Random"};
}

QSharedPointer<MoveInterface> Fiar::extractMove(QVector<HumanAction> &actions)
{
    for (int i = 0; i < actions.size(); i++)
    {
        if (actions[i].action == ActionType::MouseClick)
        {
            QSharedPointer<FiarMove> move = ModelFactory::create<FiarMove>();
            int col = getColumnFromPosition(actions[i].position);
            move->setCol(col);
            actions.clear();
            return move;
        }
    }
    actions.clear();
    return Q_NULLPTR;
}

bool Fiar::isLegalMove(FiarMove &move)
{
    int col = move.col();
    if (_finished || _board[0][col] != 0)
        return false;
    return true;
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
            QSharedPointer<FiarMove> move = ModelFactory::create<FiarMove>();
            move->setCol(i);
            moves.push_back(move);
        }
    }
    return moves;
}

int Fiar::getMaxPlayersAllowed()
{
    return 2;
}
int Fiar::getMinPlayersAllowed()
{
    return 2;
}

int Fiar::eval()
{
    return 1;
}

void Fiar::play(FiarMove &move)
{
    if (_finished)
        return ;
    int col = move.col();
    if (_board[0][col] != 0)
    {
        qWarning() << "invalid move column " << col;
        return ;
    }
    int i = 0;
    while (i < BOARD_HEIGHT && _board[i][col] == 0)
        i++;
    i--;
    _board[i][col] = _playerTurn;
    _finished = isGameFinished(col);
    if (_finished)
        _winner = _playerTurn;
    _history.push_back(FiarMove(col));

    // check total moves played (for draw)
    if (_history.size() == BOARD_HEIGHT * BOARD_WIDTH && !_finished)
    {
        _winner = 0;
        _finished = true;
    }
    _playerTurn = 3 - _playerTurn;
}

void Fiar::undo()
{
    if (_history.size() == 0)
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
    _board[i][col] = 0;
}

int Fiar::getWinner()
{
    if (!_finished)
        return -1;
    return _winner;
}

QSharedPointer<GameInterface> Fiar::clone()
{

    Fiar *fiar = new Fiar();
    fiar->_playerTurn = _playerTurn;
    fiar->_finished = _finished;
    fiar->_board = _board;
    fiar->_winner = _winner;
    fiar->_history = _history;
    QSharedPointer<GameInterface> cpy(fiar);
    return cpy;
}


bool Fiar::isGameFinished(int col)
{
    int totalAlign= 1;
    int row = 0;
    while (row < BOARD_HEIGHT && _board[row][col] == 0)
        row++;

    // check row
    int tmprow = row;
    int tmpcol = col - 1;
    totalAlign= 1;
    while (tmpcol > -1 && _board[row][tmpcol] == _playerTurn)
    {
        tmpcol--;
        totalAlign++;
    }
    tmpcol = col + 1;
    while (tmpcol < BOARD_WIDTH && _board[row][tmpcol] == _playerTurn)
    {
        tmpcol++;
        totalAlign++;
    }
    if (totalAlign >= 4)
        return true;

    // check col
    tmprow = row - 1;
    tmpcol = col;
    totalAlign= 1;
    while (tmprow > -1 && _board[tmprow][col] == _playerTurn)
    {
        tmprow--;
        totalAlign++;
    }
    tmprow = row + 1;
    while (tmprow < BOARD_HEIGHT && _board[tmprow][col] == _playerTurn)
    {
        tmprow++;
        totalAlign++;
    }
    if (totalAlign >= 4)
        return true;

    // check d1
    tmprow = row - 1;
    tmpcol = col - 1;
    totalAlign= 1;
    while (tmprow > -1 && tmpcol > -1 && _board[tmprow][tmpcol] == _playerTurn)
    {
        tmprow--;
        tmpcol--;
        totalAlign++;
    }
    tmprow = row + 1;
    tmpcol = col + 1;
    while (tmpcol < BOARD_WIDTH && tmprow < BOARD_HEIGHT && _board[tmprow][tmpcol] == _playerTurn)
    {
        tmprow++;
        tmpcol++;
        totalAlign++;
    }
    if (totalAlign >= 4)
        return true;

    // check d2
    tmprow = row - 1;
    tmpcol = col + 1;
    totalAlign= 1;
    while (tmprow > -1 && tmpcol < BOARD_WIDTH && _board[tmprow][tmpcol] == _playerTurn)
    {
        tmprow--;
        tmpcol++;
        totalAlign++;
    }
    tmprow = row + 1;
    tmpcol = col - 1;
    while (tmpcol > -1 && tmprow < BOARD_HEIGHT && _board[tmprow][tmpcol] == _playerTurn)
    {
        tmprow++;
        tmpcol--;
        totalAlign++;
    }
    if (totalAlign >= 4)
        return true;

    return false;
}




