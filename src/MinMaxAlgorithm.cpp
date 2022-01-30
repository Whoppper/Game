#include "MinMaxAlgorithm.h"

#include "GameInterface.h"
#include "MoveInterface.h"
#include <QRandomGenerator>
#include <QDebug>
#include <QThread>

void MinMaxAlgorithm::start()
{
    _start = std::chrono::high_resolution_clock::now();
    QVector<QSharedPointer<MoveInterface>> moves = _game->getMoves();
    _playerNumber = _game->playerTurn();
    if (moves.size() == 0)
    {
        qDebug() << "Error move.size == 0";
        return;
    }
    else if (moves.size() == 1)
    {
        emit resultReady(moves[0]);
        return;
    }

    int totalVisitedState = 0;
    int depth = 1;
    bool gameIsFinished = false;
    while (!isElapsed() && !gameIsFinished)
    {
        _visitedState = 0;
        int eval;
        QSharedPointer<GameInterface> gameCopy = _game->clone();
        try
        {
            QVector<QSharedPointer<MoveInterface>> principaleVariationTmp(depth);
            eval = alphabeta(gameCopy, INT_MIN, INT_MAX, depth, 0, principaleVariationTmp, 1);
            if (qAbs(eval) > 2000000000)
                gameIsFinished = true;
            _principaleVariation = principaleVariationTmp;
            qDebug() << "MinMax depth " << depth << " Eval: " << eval << " Visited States: " << _visitedState;
            totalVisitedState += _visitedState;
        }
        catch (std::exception &e)
        {
            totalVisitedState += _visitedState;
            qDebug() << "Eval: " << eval << " Visited States: " << totalVisitedState;
            QString pv;
            for (QSharedPointer<MoveInterface> &move : _principaleVariation)
            {
                if (move != nullptr)
                    pv += move->toString();
            }
            qDebug() << "PrincipaleVariation : " + pv;
            break;
        }
        depth++;
    }

    //qDebug() << _principaleVariation[0]
    emit resultReady(_principaleVariation[0]);
}

int MinMaxAlgorithm::alphabeta(QSharedPointer<GameInterface> &game, int alpha, int beta, int depth, int actualDepth, QVector<QSharedPointer<MoveInterface>> &principaleVariation, int nodeType)
{
    _visitedState++;
    int best = 0;
    if (isElapsed())
        throw std::invalid_argument("end of time");
    if (actualDepth == depth || game->finish())
    {
        if (game->finish())
        {
            if (game->getWinner() == _playerNumber)
                return INT_MAX - actualDepth;
            else if (game->getWinner() == 0)
                return 0;
            else
                return INT_MIN + actualDepth;
        }
        else
        {
            return game->eval(_playerNumber);
        }
    }
    else if (nodeType == 1)
    {
        best = INT_MIN;
        QVector<QSharedPointer<MoveInterface>> principaleVariationTmp(depth);
        QVector<QSharedPointer<MoveInterface>> moves = game->getMoves();
        //getMovessort()
        int i = 0;
        while (i < moves.size())
        {
            QSharedPointer<GameInterface> _gameTmp = game->clone();
            moves[i]->playInGame(_gameTmp);
            int ret = alphabeta(_gameTmp, alpha, beta, depth, actualDepth + 1, principaleVariationTmp, 0);
            //game->undo();
            if (ret > best)
            {
                best = ret;
                principaleVariation = principaleVariationTmp;
                principaleVariation[actualDepth] = moves[i];
            }
            if (best >= beta)
            {
                return best;
            }
            alpha = qMax(alpha, best);
            i++;
        }
    }
    else if (nodeType == 0)
    {
        best = INT_MAX;
        QVector<QSharedPointer<MoveInterface>> principaleVariationTmp(depth);
        QVector<QSharedPointer<MoveInterface>> moves = game->getMoves();
        //getMovessort()
        int i = 0;
        while (i < moves.size())
        {
            QSharedPointer<GameInterface> _gameTmp = game->clone();
            moves[i]->playInGame(_gameTmp);
            int ret = alphabeta(_gameTmp, alpha, beta, depth, actualDepth + 1, principaleVariationTmp, 1);
            //game->undo();
            if (ret < best)
            {
                best = ret;
                principaleVariation = principaleVariationTmp;
                principaleVariation[actualDepth] = moves[i];
            }
            if (best <= alpha)
            {
                return best;
            }
            beta = qMin(beta, best);
            i++;
        }
    }
    return best;
}

MinMaxAlgorithm::MinMaxAlgorithm(double timeAllowed) : AlgorithmInterface(timeAllowed)
{
}

MinMaxAlgorithm::~MinMaxAlgorithm()
{
}
