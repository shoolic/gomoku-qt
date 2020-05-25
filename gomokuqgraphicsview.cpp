#include "gomokuqgraphicsview.h"
#include "gomokuqgraphicsitem.h"
#include "gomokuqgraphicsscene.h"
#include <QGraphicsRectItem>

GomokuQGraphicsView::GomokuQGraphicsView()
{

    setRenderHint(QPainter::Antialiasing);
}

void GomokuQGraphicsView::resizeEvent(QResizeEvent* event)
{
   QGraphicsView::resizeEvent(event);
   fitInView(scene()->itemsBoundingRect() ,Qt::KeepAspectRatio);
}
