#ifndef MODELFACTORY_H
#define MODELFACTORY_H

#include <QSharedPointer>

class AlgorithmInterface;
class PlayerInterface;
class GameInterface;

class ModelFactory
{
public:
    template< class Type >
    static QSharedPointer< Type > create()
    {
        QSharedPointer< Type > ptr( new Type() );
        return ptr;
    }

    static QSharedPointer<AlgorithmInterface > createAlgoFromString(const QString &name);
    static QSharedPointer<GameInterface > createGameFromString(const QString &name);
};

#endif // MODELFACTORY_H
