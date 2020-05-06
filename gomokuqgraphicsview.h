#ifndef GOMOKUQGRAPHICSVIEW_H
#define GOMOKUQGRAPHICSVIEW_H

#include <QGraphicsView>
#include "gomokuqgraphicsscene.h"

class GomokuQGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GomokuQGraphicsView();
    void resizeEvent(QResizeEvent* event) override;
private:

};

#endif // GOMOKUQGRAPHICSVIEW_H
