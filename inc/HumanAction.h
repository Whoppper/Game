#ifndef HUMANACTION_H
#define HUMANACTION_H

#include <QPoint>
#include <QString>
#include <QMetaType>

enum class ActionType
{
    MouseClick,
    MouseRelease,
    KeyPress,
    KeyRelease
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
