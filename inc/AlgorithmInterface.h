#ifndef ALGORITHMINTERFACE_H
#define ALGORITHMINTERFACE_H

#include <QSharedPointer>
#include "MoveInterface.h"
#include <chrono>

class GameInterface;

class AlgorithmInterface : public QObject
{
    Q_OBJECT
public:
    AlgorithmInterface(double timeAllowed) : _timeAllowed(timeAllowed) {}
    virtual ~AlgorithmInterface()
    {
    }
    virtual void start() = 0;

    QSharedPointer<GameInterface> game() const
    {
        return _game;
    }
    void setGame(const QSharedPointer<GameInterface> &game)
    {
        _game = game;
    }

    int timeAllowed() const
    {
        return _timeAllowed;
    }
    void setTimeAllowed(int newTimeAllowed)
    {
        _timeAllowed = newTimeAllowed;
    }

    bool isElapsed()
    {
        std::chrono::duration<double> elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::high_resolution_clock::now() - _start);
        return (elapsed.count() >= _timeAllowed);
    }

protected:
    QSharedPointer<GameInterface> _game;
    std::chrono::high_resolution_clock::time_point _start;
    double _timeAllowed;

signals:
    void resultReady(MovePtr move);
};

#endif // ALGORITHMINTERFACE_H
