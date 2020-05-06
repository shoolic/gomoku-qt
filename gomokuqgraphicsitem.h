#ifndef GOMOKUQGRAPHICSITEM_H
#define GOMOKUQGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QObject>

class GomokuQGraphicsItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)

public:
    GomokuQGraphicsItem();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    enum class State {
        Empty,
        White,
        Black,
        Winning,
    };
    State state;
};

#endif // GOMOKUQGRAPHICSITEM_H
