#ifndef GAMEUI_H
#define GAMEUI_H

#include <QWidget>
#include <QSharedDataPointer>
#include <QPainter>


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

private:
    QSharedPointer<GameInterface> _game;

signals:

};

#endif // GAMEUI_H
