#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include <QVector>
#include <QSharedPointer>
#include <QScopedPointer>

class PlayerInterface;
class GameInterface;

class GameController : public QObject
{
    Q_OBJECT
public:

    explicit GameController(QObject *parent = nullptr);

    void addPlayer(QSharedPointer<PlayerInterface> player);

signals:


private:
    QVector<QSharedPointer<PlayerInterface>> _players;
    //QScopedPointer<GameInterface> _game;




};

#endif // GAMECONTROLLER_H
