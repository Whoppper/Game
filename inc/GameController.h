#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

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

signals:
    void gameChanged();

public slots:
    void addPlayer(QSharedPointer<PlayerInterface> player);
    void moveReceived(QSharedPointer<MoveInterface> move);


private:
    QVector<QSharedPointer<PlayerInterface>> _players;
    QSharedPointer<GameInterface> _game;
    bool _gameInProgress;

};

#endif // GAMECONTROLLER_H
