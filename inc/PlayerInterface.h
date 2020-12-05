#ifndef PLAYERINTERFACE_H
#define PLAYERINTERFACE_H

#include <QSharedPointer>
#include <QObject>


class GameInterface;
class MoveInterface;
class GameUI;
class GameController;

class PlayerInterface : public QObject
{
    Q_OBJECT
public:
    PlayerInterface() {};
    PlayerInterface(const QSharedPointer<GameInterface> game) : _game(game) {};
    virtual void think() = 0;
    virtual void setConnection(QSharedPointer<GameUI> ui, QSharedPointer<GameController> controller)= 0;
    void setGame(QSharedPointer<GameInterface> game) {_game = game;}
    void setPlayerNum(int num) {_playerNum = num;}
    int PlayerNum() {return _playerNum;}



signals:
    void sendMove(QSharedPointer<MoveInterface> move);


protected:
    QSharedPointer<GameInterface> _game;
    int _playerNum;

};


#endif // PLAYERINTERFACE_H
