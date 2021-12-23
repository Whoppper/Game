#ifndef MCTSALGORITHM_H
#define MCTSALGORITHM_H

#include "AlgorithmInterface.h"
#include <QSharedPointer>

class MoveInterface;
class GameInterface;


class MctsNode
{
public:
    MctsNode();
    MctsNode(int player);
    ~MctsNode();
    int _visit;
    double _win;
    int _player;
    MctsNode *_parent;
    //QSharedPointer<MctsNode> _parent;
    QSharedPointer<GameInterface> _game;
    QVector<QSharedPointer<MctsNode>> _children;
    QSharedPointer<MoveInterface> _move;
    QSharedPointer<MctsNode> getBestUctChild();
    void backPropagation(int winner);
    void expand();
    double getUct();
};

class MctsAlgorithm : public AlgorithmInterface
{
    Q_OBJECT
public:
    MctsAlgorithm(double timeAllowed);
    virtual ~MctsAlgorithm();
    virtual void start() override;

    static constexpr double WIN_SCORE = 1;
    static constexpr double DRAW_SCORE = 0.5;

    int simulateRandomPlayout(QSharedPointer<GameInterface> game);
    QSharedPointer<MctsNode> selectPromisingNode(QSharedPointer<MctsNode> &node);




private:
    int _playerNumber;
    QSharedPointer<MctsNode> _root;
    int _rollout;


};

#endif // MCTSALGORITHM_H
