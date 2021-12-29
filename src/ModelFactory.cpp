#include "ModelFactory.h"

#include "AlgorithmInterface.h"
#include "RandomAlgorithm.h"
#include "MinMaxAlgorithm.h"
#include "MctsAlgorithm.h"
#include "PlayerInterface.h"
#include "IA.h"
#include "Human.h"

#include "GameInterface.h"
#include "Fiar.h"
#include "Uttt.h"

QSharedPointer<AlgorithmInterface > ModelFactory::createAlgoFromString(const QString &name)
{
    QSharedPointer<AlgorithmInterface > algo;
    if (name == "Random")
    {
        algo = ModelFactory::create<RandomAlgorithm>(1);
    }
    else if (name == "MinMax")
    {
        algo = ModelFactory::create<MinMaxAlgorithm>(1);
    }
    else if (name == "Mcts")
    {
        algo = ModelFactory::create<MctsAlgorithm>(1);
    }
    return (algo);
}

QSharedPointer<GameInterface > ModelFactory::createGameFromString(const QString &name)
{
    QSharedPointer<GameInterface> game;
    if (name == "Fiar")
    {
        game = ModelFactory::create<Fiar>();
    }
    else if (name == "Uttt")
    {
        game = ModelFactory::create<Uttt>();
    }
    return (game);
}
