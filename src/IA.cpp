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

IA::IA(QSharedPointer<GameInterface> game, QSharedPointer<AlgorithmInterface> algorithm) :
PlayerInterface(game), _algorithm(algorithm)
{

}

void IA::think()
{
    qDebug() << "IA is thinking...";
    _thread = new QThread();
    _algorithm->moveToThread(_thread);
    _algorithm->setGame(_game);
    connect(_thread, &QThread::finished, _thread, &QObject::deleteLater);
    connect(_thread, &QThread::started, _algorithm.get(), &AlgorithmInterface::start);
    connect(_algorithm.get(), &AlgorithmInterface::resultReady, this, &IA::onResultReady);
    _thread->start();

}

void IA::setAlgorithm(const QSharedPointer<AlgorithmInterface> &algorithm)
{
    _algorithm = algorithm;
}

void IA::setConnection(QSharedPointer<GameUI> ui, QSharedPointer<GameController> controller)
{
    Q_UNUSED(ui);
    connect(this, &IA::sendMove, controller.get(), &GameController::moveReceived);
}

void IA::onResultReady(MovePtr move)
{
    qDebug() << "IA send move..." << move;
    emit sendMove(move);
}

IA::~IA()
{

}
