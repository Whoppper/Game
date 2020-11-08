#ifndef PLAYERINTERFACE_H
#define PLAYERINTERFACE_H

#include <QSharedPointer>
#include <QObject>
#include "GameInterface.h"
class MoveInterface;

class PlayerInterface : public QObject
{
    Q_OBJECT
public:
    PlayerInterface(const QSharedPointer<GameInterface> game) : _game(game) {};
    virtual void think() = 0;
    void setGame(QSharedPointer<GameInterface> game) {_game = game;}
    void setPlayerNum(int num) {_playerNum = num;}
    int PlayerNum() {return _playerNum;}


//signals:
//    void sendMove(QSharedPointer<MoveInterface> move);


protected:
    QSharedPointer<GameInterface> _game;
    int _playerNum;

};


#endif // PLAYERINTERFACE_H
