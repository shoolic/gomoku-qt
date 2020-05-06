#ifndef GOMOKUQGRAPHICSSCENE_H
#define GOMOKUQGRAPHICSSCENE_H
#include "gomokuqgraphicsitem.h"
#include <QGraphicsScene>
#include <vector>

class GomokuQGraphicsScene : public QGraphicsScene
{
    Q_OBJECT


public:
    GomokuQGraphicsScene();

    void init();
    QString getWhiteNick();
    QString getBlackNick();
    void setWhiteNick(QString nick);
    void setBlackNick(QString nick);
    void updateInfo();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent2(QGraphicsSceneMouseEvent *event);

private:
    QString whiteNick_;
    QString blackNick_;
    GomokuQGraphicsItem::State currentInsertState;
    std::vector<std::vector<GomokuQGraphicsItem*>> board;
    QGraphicsRectItem *stones;

    QGraphicsRectItem *grid;
    QPen gridPen;
    void paintGrid();

    enum class GameState {
        BlackTurn,
        WhiteTurn,
        BlackWins,
        WhiteWins
    };

    GameState gameState;
    void setState(GameState state);

// EXPAND
    QRect boardRect;
    static const int detectExpandSize = 1;
    static const int expandSize = 2;
    void tryExpand(QPoint p);
    void expandTop();
    void expandBottom();
    void expandLeft();
    void expandRight();

// WIN COMBINATION
    static const int stonesToWin = 5;

    struct Stone {
        int x;
        int y;
        Stone(int x, int y): x(x), y(y) {}
    };

    struct Direction {
        Stone start;
        Stone end;
        int count;
        int moveXBackward;
        int moveYBackward;
        int moveXForward;
        int moveYForward;
        Direction(int x, int y,
                  int moveXBackward,
                    int moveYBackward,
                    int moveXForward,
                    int moveYForward):
            start(x,y),
            end(x+moveXForward,y+moveYForward),
            count(1),
            moveXBackward(moveXBackward),
            moveYBackward(moveYBackward),
            moveXForward(moveXForward),
            moveYForward(moveYForward)
        {}
    };

    struct Directions {
        Direction arr[4];
        Directions(int x, int y):
            arr {
                {x, y,  0, -1,  0, 1},
                {x, y, -1,  0,  1, 0},
                {x, y, -1, -1,  1, 1},
                {x, y,  1, -1, -1, 1}
            }
        {}
    };

    bool tryWin(int x, int y);
    int countDir(Direction &dir);
    int countDirBackward(Direction &dir);
    int countDirForward(Direction &dir);
    bool inBoard(int x, int y);
    bool sameState(int x, int y);
    void markAsWin(Direction &dir);

signals:
    void infoChanged(QString);
};
#endif // GOMOKUQGRAPHICSSCENE_H
