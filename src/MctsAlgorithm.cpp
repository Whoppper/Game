#include "MctsAlgorithm.h"

#include "GameInterface.h"
#include "MoveInterface.h"
#include "ModelFactory.h"
#include <QRandomGenerator>
#include <QDebug>
#include <QThread>
#include <QtMath>

MctsNode::MctsNode() : _visit(0), _win(0), _parent(nullptr), _game(nullptr)
{
}

MctsNode::MctsNode(int player) : _visit(0), _win(0), _player(player), _parent(nullptr), _game(nullptr)
{
}

MctsNode::~MctsNode()
{
}

double MctsNode::getUct()
{
    if (_parent == nullptr)
        return 0;
    if (_visit == 0)
        return INT_MAX;
    double uct;
    uct = (_win / _visit) + 1.41 * qPow(qLn((double)_parent->_visit) / (double)_visit, 0.5);
    return uct;
}

void MctsNode::expand()
{
    if (_game->finish() || _children.size() > 0)
        return;
    QVector<QSharedPointer<MoveInterface>> moves = _game->getMoves();
    for (QSharedPointer<MoveInterface> &move : moves)
    {
        QSharedPointer<MctsNode> child = ModelFactory::create<MctsNode>(3 - _player);
        child->_parent = this;
        child->_player = 3 - _player;
        child->_game = _game->clone();
        move->playInGame(child->_game);
        child->_move = move;
        _children.push_back(child);
    }
}

QSharedPointer<MctsNode> MctsNode::getBestUctChild()
{
    double bestUct = INT_MIN;
    QSharedPointer<MctsNode> bestNode = nullptr;
    for (QSharedPointer<MctsNode> &child : _children)
    {
        double tmpUct = child->getUct();
        if (tmpUct > bestUct)
        {
            bestUct = tmpUct;
            bestNode = child;
        }
    }
    return bestNode;
}

void MctsAlgorithm::start()
{

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
    _root = ModelFactory::create<MctsNode>(3 - _playerNumber);
    _root->_game = _game;
    _rollout = 0;
    _start = std::chrono::high_resolution_clock::now();
    while (!isElapsed())
    {
        _rollout++;
        QSharedPointer<MctsNode> node = selectPromisingNode(_root);
        node->expand();
        node = selectPromisingNode(node);
        int winner = simulateRandomPlayout(node->_game->clone());
        node->backPropagation(winner);
    }
    if (_root->_children.size() == 0)
    {
        qDebug() << "problem root no child  ";
        return;
    }
    QSharedPointer<MctsNode> bestNode = _root->_children.at(0);
    for (QSharedPointer<MctsNode> &child : _root->_children)
    {
        if (child->_visit > bestNode->_visit)
            bestNode = child;
    }
    qDebug() << "_rollout: " << _rollout;
    qDebug() << "visite: " << bestNode->_visit;
    qDebug() << "win: " << bestNode->_win;
    qDebug() << "ratio: " << bestNode->_win / bestNode->_visit;
    emit resultReady(bestNode->_move);
}

void MctsNode::backPropagation(int winner)
{
    _visit++;
    if (winner == _player)
    {
        _win += MctsAlgorithm::WIN_SCORE;
    }
    else if (winner == 0)
    {
        _win += MctsAlgorithm::DRAW_SCORE;
    }
    if (_parent)
        _parent->backPropagation(winner);
}

int MctsAlgorithm::simulateRandomPlayout(QSharedPointer<GameInterface> game)
{
    while (!game->finish())
    {
        QVector<QSharedPointer<MoveInterface>> moves = game->getMoves();
        moves[rand() % moves.size()]->playInGame(game);
    }
    return game->getWinner();
}

QSharedPointer<MctsNode> MctsAlgorithm::selectPromisingNode(QSharedPointer<MctsNode> &node)
{
    QSharedPointer<MctsNode> tmpNode = node;
    while (tmpNode->_children.size() != 0)
    {
        tmpNode = tmpNode->getBestUctChild();
    }
    return tmpNode;
}

MctsAlgorithm::MctsAlgorithm(double timeAllowed) : AlgorithmInterface(timeAllowed), _root(nullptr), _rollout(0)
{
}

MctsAlgorithm::~MctsAlgorithm()
{
}
