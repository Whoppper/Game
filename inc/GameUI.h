#ifndef GAMEUI_H
#define GAMEUI_H

#include <QWidget>
#include <QSharedDataPointer>
#include <QPainter>
#include "HumanAction.h"

class Fiar;
class Uttt;
class GameInterface;

class GameUI : public QWidget
{
    Q_OBJECT
public:
    GameUI(QWidget *parent = nullptr, QSharedPointer<GameInterface> game =nullptr);
    void displayGame(Fiar &fiar);
    void displayGame(Uttt &uttt);
    QSharedPointer<GameInterface> game() const;
    void setGame(const QSharedPointer<GameInterface> &game);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

public slots:
    void needToRefresh();


signals:
    void newHumanAction(HumanAction action);

private:
    QSharedPointer<GameInterface> _game;

signals:

};

#endif // GAMEUI_H
