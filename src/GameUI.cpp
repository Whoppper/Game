#include "GameUI.h"

#include "GameInterface.h"
#include "Fiar.h"
#include "Uttt.h"
#include <QDebug>
#include <QMouseEvent>


GameUI::GameUI(QWidget *parent, QSharedPointer<GameInterface> game) : QWidget(parent), _game(game)
{
    if (_game != Q_NULLPTR)
    {
        setMinimumSize(QSize(_game->getMinimumWidth(), _game->getMinimumHeight()));
        setMaximumSize(QSize(_game->getMinimumWidth(), _game->getMinimumHeight()));
    }
}


void GameUI::paintEvent(QPaintEvent *event)
{
    //qDebug() << "paintEvent";
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

QSharedPointer<GameInterface> GameUI::game() const
{
    return _game;
}

void GameUI::setGame(const QSharedPointer<GameInterface> &game)
{
    _game = game;
    setMinimumSize(QSize(_game->getMinimumWidth(), _game->getMinimumHeight()));
    setMaximumSize(QSize(_game->getMinimumWidth(), _game->getMinimumHeight()));
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
            int x = Fiar::COLSIZE / 2 + Fiar::COLSIZE * col;
            int y = Fiar::COLSIZE / 2 + Fiar::COLSIZE * row;
            painter.drawEllipse(QPointF(x,y), Fiar::COLSIZE / 2, Fiar::COLSIZE / 2);
        }
    }
    painter.end();
}

void GameUI::displayGame(Uttt &uttt)
{
    QPainter painter;
    painter.begin(this);
    QPen pen(Qt::black);

    painter.setPen(pen);
    painter.fillRect(rect(), pen.brush());
    QVector<QColor> colors = {Qt::white, Qt::yellow, Qt::cyan};
    QVector<QVector<QVector<int>>> boards = uttt.boards();
    QVector<QVector<int>> board = uttt.board();
    painter.setPen(QPen(Qt::red));
    painter.drawLine(180, 0, 180, 540);
    painter.drawLine(360, 0, 360, 540);
    painter.drawLine(0, 180, 540, 180);
    painter.drawLine(0, 360, 540, 360);

    int i = 0;
    for (const QVector<QVector<int>> &ttt : boards)
    {
        int urow = i / 3;
        int ucol = i % 3;
        if (board[urow][ucol] == 1 || board[urow][ucol] == 2)
        {

            pen = QPen(colors[board[urow][ucol]]);
            pen.setWidth(4);
            painter.setPen(pen);
            if (board[urow][ucol] == 1)
            {
                painter.drawLine(ucol * 180, urow * 180, (1 + ucol) * 180, (1 + urow) * 180);
                painter.drawLine(ucol * 180 + 180, urow * 180, (ucol) * 180, (1 + urow) * 180);
            }
            else
            {
                painter.drawEllipse(QPointF(ucol * 180 + 90 ,urow * 180 + 90), 90, 90);
            }
            i++;
            continue;
        }

        pen = QPen(colors[0]);
        pen.setWidth(2);
        painter.setPen(pen);
        int topLeftCPos = ucol * 180;
        int topLeftRPos = urow * 180;

        painter.drawLine(topLeftCPos + 60, topLeftRPos, topLeftCPos + 60, topLeftRPos + 180);
        painter.drawLine(topLeftCPos + 120, topLeftRPos, topLeftCPos + 120, topLeftRPos + 180);
        painter.drawLine(topLeftCPos, topLeftRPos + 60, topLeftCPos + 180, topLeftRPos + 60);
        painter.drawLine(topLeftCPos, topLeftRPos + 120, topLeftCPos + 180, topLeftRPos + 120);

        for (int row = 0; row < ttt.size(); row++)
        {
            for (int col = 0; col < ttt[row].size(); col++)
            {
                int topLeftCPos = ucol * 180 + 60 * col;
                int topLeftRPos = urow * 180 + 60 * row;
                if (ttt[row][col] == 1 || ttt[row][col] == 2)
                {
                    pen = QPen(colors[ttt[row][col]]);
                    pen.setWidth(2);
                    painter.setPen(pen);
                    if (ttt[row][col] == 1)
                    {
                        painter.drawLine(topLeftCPos, topLeftRPos, topLeftCPos + 60, topLeftRPos + 60);;
                        painter.drawLine(topLeftCPos + 60, topLeftRPos, topLeftCPos, topLeftRPos + 60);
                    }
                    else
                    {
                        painter.drawEllipse(QPointF(topLeftCPos + 30 ,topLeftRPos + 30), 30, 30);
                    }
                }
                if (uttt.isLegal(urow * 3 + row, ucol * 3 + col))
                {
                    pen = QPen(Qt::green);
                    pen.setWidth(2);
                    painter.setPen(pen);
                    painter.drawEllipse(QPointF(topLeftCPos + 30 ,topLeftRPos + 30), 3, 3);
                }
            }
        }

        i++;
    }
    painter.end();
}

void GameUI::mousePressEvent(QMouseEvent *event)
{
    //qDebug() << "GameUI::mousePressEvent";
    HumanAction haction;
    haction.action = ActionType::MouseClick;
    haction.position = event->pos();
    emit newHumanAction(haction);
}
