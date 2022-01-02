#ifndef NEWGAMEDIALOG_H
#define NEWGAMEDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QVector>
#include <QLayout>
#include <QSharedPointer>
#include <QComboBox>
#include <QPushButton>

#include "GameInterface.h"
#include "mainwindow.h"

class PlayerInterface;
class GameInterface;


class NewGameDialog : public QDialog
{
    Q_OBJECT
public:

    explicit NewGameDialog(QDialog *parent = nullptr);
    QVector<QSharedPointer<PlayerInterface> > players() const;
    QSharedPointer<GameInterface> game() const;
    void resetDialog();

private:

    QVector<QSharedPointer<PlayerInterface>> _players;
    QSharedPointer<GameInterface> _game;

    QComboBox *_gameCombo;
    QVector<QComboBox *> _playerCombo;
    QVector<QComboBox *> _algoCombo;

    QVBoxLayout *_vlayout;
    QHBoxLayout *_hlayout;
    QPushButton *_valider;
    QWidget *_playerWidget;


private slots:
    void createGame();
    void gameSelected(const QString &gameName);

};

#endif // NEWGAMEDIALOG_H
