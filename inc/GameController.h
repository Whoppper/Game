#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "HumanAction.h"
#include <QObject>
#include <QVector>
#include <QSharedPointer>
#include <QScopedPointer>

class PlayerInterface;
class GameInterface;
class MoveInterface;

class GameController : public QObject
{
    Q_OBJECT
public:
    explicit GameController(QObject *parent = nullptr);
    void setGame(QSharedPointer<GameInterface> game);
    void startGame();
    void clear();

signals:
    void gameChanged();

public slots:
    void addPlayer(QSharedPointer<PlayerInterface> player);
    void moveReceived(QSharedPointer<MoveInterface> move);
    void onHumanAction(HumanAction action);

private:
    QVector<QSharedPointer<PlayerInterface>> _players;
    QSharedPointer<GameInterface> _game;
    bool _gameInProgress;
    int _playerTurn;
};

#endif // GAMECONTROLLER_H
