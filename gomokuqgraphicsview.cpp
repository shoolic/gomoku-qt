#include "gomokuqgraphicsview.h"
#include "gomokuqgraphicsitem.h"
#include "gomokuqgraphicsscene.h"
#include <QGraphicsRectItem>

GomokuQGraphicsView::GomokuQGraphicsView()
{
    GomokuQGraphicsScene *scene = new GomokuQGraphicsScene;
    setStyleSheet("background: transparent");
    setScene(scene);
    setRenderHint(QPainter::Antialiasing);
}

void GomokuQGraphicsView::resizeEvent(QResizeEvent* event)
{
   QGraphicsView::resizeEvent(event);
   fitInView(scene()->itemsBoundingRect() ,Qt::KeepAspectRatio);
}
