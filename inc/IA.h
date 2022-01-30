#ifndef IA_H
#define IA_H

#include "PlayerInterface.h"
#include "MoveInterface.h"
#include <QSharedPointer>
#include <QThread>
#include <QMetaType>

class GameInterface;
class AlgorithmInterface;

class IA : public PlayerInterface
{
    Q_OBJECT
public:
    virtual ~IA();
    IA();
    IA(QSharedPointer<GameInterface> game, QSharedPointer<AlgorithmInterface> algorithm);
    virtual void think() override;
    void setAlgorithm(const QSharedPointer<AlgorithmInterface> &algorithm);
    virtual void setConnection(QSharedPointer<GameUI> ui, QSharedPointer<GameController> controller) override;

signals:
    void operate();

private slots:
    void onResultReady(MovePtr move);

private:
    QThread *_thread;
    QSharedPointer<AlgorithmInterface> _algorithm;
};

//Q_DECLARE_METATYPE(QSharedPointer<MoveInterface>);

#endif // IA_H
