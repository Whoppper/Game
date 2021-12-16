#include "NewGameDialog.h"
#include <QDebug>

#include "MoveInterface.h"
#include "RandomAlgorithm.h"
#include "AlgorithmInterface.h"
#include "IA.h"
#include "Human.h"
#include "GameUI.h"
#include "GameController.h"
#include "ModelFactory.h"
#include "Fiar.h"


const QStringList NewGameDialog::gameList = {"None", "Fiar"};

NewGameDialog::NewGameDialog(QDialog *parent) : QDialog(parent)
{
    _vlayout = new QVBoxLayout(this);
    _playerWidget = new QWidget(this);
    _hlayout = new QHBoxLayout();
    _gameCombo = new QComboBox(this);
    _gameCombo->insertItems(0, gameList);
    _valider= new QPushButton("OK", this);
    layout()->addWidget(_gameCombo);
    _playerWidget->setLayout(_hlayout);
    layout()->addWidget(_playerWidget);
    layout()->addWidget(_valider);
    connect(_valider, &QPushButton::clicked, this, &NewGameDialog::createGame);
    connect(_gameCombo, &QComboBox::currentTextChanged, this, &NewGameDialog::gameSelected);
    resize(600, 400);
}

void NewGameDialog::resetDialog()
{
    for (QComboBox *combo : _algoCombo)
    {
        delete combo;
    }
    for (QComboBox *combo : _playerCombo)
    {
        delete combo;
    }
    _algoCombo.clear();
    _playerCombo.clear();
    _game.clear();
    _players.clear();
}


void NewGameDialog::gameSelected(const QString &gameName)
{
    QSharedPointer<GameInterface> tmpgame = ModelFactory::createGameFromString(gameName);

    int maxPlayers = tmpgame->getMaxPlayersAllowed();
    for (int i = 0; i < maxPlayers; i++)
    {
        QComboBox *combo = new QComboBox(this);
        combo->addItems(tmpgame->playerAllowed());
        QComboBox *combo2 = new QComboBox(this);
        combo2->addItems(tmpgame->algorithmAllowedForIa());
        _hlayout->addWidget(combo);
        _hlayout->addWidget(combo2);
        _playerCombo.push_back(combo);
        _algoCombo.push_back(combo2);
    }
}

QVector<QSharedPointer<PlayerInterface> > NewGameDialog::players() const
{
    return _players;
}

QSharedPointer<GameInterface> NewGameDialog::game() const
{
    return _game;
}

void NewGameDialog::createGame()
{
    _players.clear();
    _game = ModelFactory::createGameFromString(_gameCombo->currentText());
    int nbPlayers = 0;
    for (QComboBox *combo : _playerCombo)
    {
        if (combo->currentText() != "None")
            nbPlayers++;
    }
    if (nbPlayers < _game->getMinPlayersAllowed())
    {
        //qDebug() << "Minimun Players: " << _game->getMinPlayersAllowed() << " " << nbPlayers;
        QDialog::reject();
        return ;
    }

    int i = 0;
    while (i < _playerCombo.size() && i < _algoCombo.size())
    {
        if (_playerCombo[i]->currentText() == "IA")
        {
            QSharedPointer<AlgorithmInterface> algo = ModelFactory::createAlgoFromString(_algoCombo[i]->currentText());
            IA *ia = new IA(_game->clone(), algo);
            QSharedPointer<PlayerInterface> p (ia);
            _players.push_back(p);
        }
        else if (_playerCombo[i]->currentText() == "Human")
        {
            Human *human = new Human(_game->clone());
            QSharedPointer<PlayerInterface> p (human);
            _players.push_back(p);
        }
        i++;
    }
    emit playersCreated(_players);
    emit gameCreated(_game);
    QDialog::accept();
}







