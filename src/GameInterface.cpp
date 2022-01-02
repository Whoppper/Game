#include "GameInterface.h"

const QVector<GameName> GameInterface::gameList = {GameName::Fiar, GameName::Uttt};

QString GameInterface::GameNameToString(GameName name)
{
    if (name == GameName::Fiar)
    {
        return "Fiar";
    }
    else if (name == GameName::Uttt)
    {
        return "Uttt";
    }
    return "None";
}
