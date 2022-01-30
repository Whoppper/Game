#include "IA.h"

#include "AlgorithmInterface.h"
#include "GameInterface.h"
#include "MoveInterface.h"
#include "GameController.h"

#include "FiarMove.h"
#include <QObject>
#include <QDebug>

IA::IA()
{
}

IA::IA(QSharedPointer<GameInterface> game, QSharedPointer<AlgorithmInterface> algorithm) : PlayerInterface(game), _algorithm(algorithm)
{

    _thread = new QThread();
    _algorithm->moveToThread(_thread);
    connect(_algorithm.get(), &AlgorithmInterface::resultReady, this, &IA::onResultReady);
    connect(_thread, &QThread::started, _algorithm.get(), &AlgorithmInterface::start);
}

void IA::think()
{
    qDebug() << "IA is thinking...";
    _algorithm->setGame(_game);
    _thread->start();
}

void IA::setAlgorithm(const QSharedPointer<AlgorithmInterface> &algorithm)
{
    _algorithm = algorithm;
    connect(_algorithm.get(), &AlgorithmInterface::resultReady, this, &IA::onResultReady);
}

void IA::setConnection(QSharedPointer<GameUI> ui, QSharedPointer<GameController> controller)
{
    Q_UNUSED(ui);
    connect(this, &IA::sendMove, controller.get(), &GameController::moveReceived);
}

void IA::onResultReady(MovePtr move)
{
    //qDebug() << "IA send move..." << move;
    _thread->quit();
    emit sendMove(move);
}

IA::~IA()
{
    if (_thread)
    {
        _thread->quit();
        if (!_thread->wait(3000))
        {
            qDebug() << "call thread terminate";
            _thread->terminate();
            _thread->wait();
        }
        delete _thread;
        _thread = nullptr;
    }
}
