#ifndef ALGORITHMINTERFACE_H
#define ALGORITHMINTERFACE_H

#include <QSharedPointer>
#include "MoveInterface.h"

class GameInterface;
class MoveInterface;

class AlgorithmInterface : public QObject
{

    Q_OBJECT
public:
    virtual ~AlgorithmInterface() {}
    virtual QSharedPointer<MoveInterface> start() = 0;

    QSharedPointer<GameInterface> game() const {return _game;}
    void setGame(const QSharedPointer<GameInterface> &game) {_game = game;}
protected:
    QSharedPointer<GameInterface> _game;

signals:
    void resultReady(MovePtr move);

};







#endif // ALGORITHMINTERFACE_H


