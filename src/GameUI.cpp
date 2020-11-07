#include "GameUI.h"

#include "GameInterface.h"
#include "Fiar.h"
#include <QDebug>

GameUI::GameUI(QWidget *parent, QSharedPointer<GameInterface> game) : QWidget(parent), _game(game)
{
    setMinimumSize(QSize(800, 800));
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
            int x = 30 + 70 * col;
            int y = 30 + 70 * row;
            painter.drawEllipse(QPointF(x,y), 30, 30);
        }
    }
    painter.end();
}
