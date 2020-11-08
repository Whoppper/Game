#include "GameUI.h"

#include "GameInterface.h"
#include "Fiar.h"
#include <QDebug>
#include <QMouseEvent>

GameUI::GameUI(QWidget *parent, QSharedPointer<GameInterface> game) : QWidget(parent), _game(game)
{
    setMinimumSize(QSize(_game->getMinimumWidth(), _game->getMinimumHeight()));
    setMaximumSize(QSize(_game->getMinimumWidth(), _game->getMinimumHeight()));
}


void GameUI::paintEvent(QPaintEvent *event)
{
    qDebug() << "paintEvent";
    Q_UNUSED(event);
    if (_game != nullptr)
    {
        _game->display(*this);
    }
}

void GameUI::needToRefresh(/*GameInterface g*/)
{
    update();
}

void GameUI::displayGame(Fiar &fiar)
{
    QPainter painter;
    painter.begin(this);
    QBrush brush(Qt::black);
    painter.setBrush(brush);
    painter.fillRect(rect(), brush);
    QVector<QColor> colors = {Qt::white, Qt::yellow, Qt::red};
    const QVector<QVector<int>> &board = fiar.getBoard();
    for (int row = 0; row < board.size(); row++)
    {
        for (int col = 0; col < board[row].size(); col++)
        {
            painter.setBrush(QBrush(colors[board[row][col]]));
            int x = 35 + 70 * col;
            int y = 35 + 70 * row;
            painter.drawEllipse(QPointF(x,y), 35, 35);
        }
    }
    painter.end();
}

void GameUI::mousePressEvent(QMouseEvent *event)
{
    HumanAction haction;
    haction.action = ActionType::MOUSE_PRESS;
    haction.position = event->pos();
    emit newHumanAction(haction);
}
