#include "gomokuqgraphicsitem.h"

#include <QPainter>

GomokuQGraphicsItem::GomokuQGraphicsItem()
{

}
void GomokuQGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    switch(state) {
     case State::White:
        painter->setBrush(QBrush(Qt::white));
        break;
    case State::Black:
       painter->setBrush(QBrush(Qt::black));
       break;
    case State::Winning:
       painter->setBrush(QBrush(Qt::red));
       break;
    default:
        return;
    }

    painter->setPen(QPen(Qt::black, 0.05));
    painter->drawEllipse(QRectF(0.05,0.05, 0.9,0.9));
}

QRectF GomokuQGraphicsItem::boundingRect() const {
   return QRectF(0, 0, 1, 1);
}

