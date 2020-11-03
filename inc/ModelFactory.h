#ifndef MODELFACTORY_H
#define MODELFACTORY_H

#include <QSharedPointer>

class ModelFactory
{
public:
    template< class Type >
    static QSharedPointer< Type > create()
    {
        QSharedPointer< Type > ptr( new Type() );
        return ptr;
    }

};

#endif // MODELFACTORY_H
