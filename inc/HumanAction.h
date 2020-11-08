#ifndef HUMANACTION_H
#define HUMANACTION_H

#include <QPoint>
#include <QString>
#include <QMetaType>

enum class ActionType
{
    MOUSE_PRESS,
    MOUSE_RELEASE,
    KEY_PRESS,
    KEY_RELEASE
};


class HumanAction
{
public:

    ActionType action;
    QPoint position;
    QString data;

};

Q_DECLARE_METATYPE(HumanAction);

#endif // HUMANACTION_H
