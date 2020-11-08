#ifndef GAMEUI_H
#define GAMEUI_H

#include <QWidget>
#include <QSharedDataPointer>
#include <QPainter>
#include "HumanAction.h"

class Fiar;
class GameInterface;

class GameUI : public QWidget
{
    Q_OBJECT
public:
    explicit GameUI(QWidget *parent = nullptr, QSharedPointer<GameInterface> game =nullptr);
    void displayGame(Fiar &fiar);
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    //TODO gerer les autres events

public slots:
    void needToRefresh(/*GameInterface g*/);


signals:
    void newHumanAction(HumanAction action);

private:
    QSharedPointer<GameInterface> _game;

signals:

};

#endif // GAMEUI_H
