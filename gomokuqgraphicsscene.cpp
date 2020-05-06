#include "gomokuqgraphicsscene.h"
#include "gomokuqgraphicsitem.h"
#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>
#include <QtMath>

GomokuQGraphicsScene::GomokuQGraphicsScene() :
    whiteNick_("White"),
    blackNick_("Black"),
    currentInsertState(GomokuQGraphicsItem::State::Black),
    board{},
    gridPen(QPen(Qt::darkGray, 0.1, Qt::SolidLine))
{}

void GomokuQGraphicsScene::init() {
    setSceneRect(0, 0, 0, 0);
    paintGrid();
    stones = addRect(0, 0, 0,0, Qt::NoPen);
    setState(GameState::BlackTurn);
}


QString GomokuQGraphicsScene::getWhiteNick() {
    return whiteNick_;
}

QString GomokuQGraphicsScene::getBlackNick() {
    return blackNick_;
}


void GomokuQGraphicsScene::setWhiteNick(QString nick) {
    whiteNick_ = nick;
    updateInfo();
}

void GomokuQGraphicsScene::setBlackNick(QString nick) {
    blackNick_ = nick;
    updateInfo();
}

void GomokuQGraphicsScene::setState(GameState state) {
    gameState = state;
    updateInfo();
}

void GomokuQGraphicsScene::updateInfo() {
    switch(gameState) {
    case GameState::BlackTurn:
        emit infoChanged(blackNick_ + "'s turn!");
        break;
    case GameState::WhiteTurn:
         emit infoChanged(whiteNick_ + "'s turn!");
        break;
    case GameState::BlackWins:
         emit infoChanged(blackNick_ + " won!");
        break;
    case GameState::WhiteWins:
         emit infoChanged(whiteNick_ + " won!");
        break;
    }
}



void GomokuQGraphicsScene::paintGrid() {
    grid = addRect(0,0,0,0, Qt::NoPen);
    grid->moveBy(0.5, 0.5);
    boardRect.adjust(-1,-1,1,1);

    board.push_back(std::vector<GomokuQGraphicsItem*>(3));
    board.push_back(std::vector<GomokuQGraphicsItem*>(3));
    board.push_back(std::vector<GomokuQGraphicsItem*>(3));

    for(int y= -1; y<1; y++) {
        for(int x = -1; x < 1; x++) {
            auto *item = addRect(x, y, 1, 1, gridPen);
            item->setParentItem(grid);
        }
    }
}

void GomokuQGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(gameState == GameState::BlackWins || gameState == GameState::WhiteWins) {
        return;
    }

    const QPointF pF = (event->scenePos());
    QPoint pGrid(qFloor(pF.x()),qFloor(pF.y()));
    QPoint p(pGrid.x() - boardRect.left(), pGrid.y() - boardRect.top());

    if(!inBoard(p.x(),p.y())) {
        return;
    }

    if(board[p.y()][p.x()] != nullptr){
        return;
    }

    auto item = new GomokuQGraphicsItem;
    addItem(item);
    item->setParentItem(stones);
    item->setPos(pGrid);
    item->state = currentInsertState;
    board[p.y()][p.x()] = item;

    if(tryWin(p.x(), p.y())) {
        return;
    }

    if(currentInsertState == GomokuQGraphicsItem::State::Black) {
        currentInsertState = GomokuQGraphicsItem::State::White;
        setState(GameState::WhiteTurn);
    } else if(currentInsertState == GomokuQGraphicsItem::State::White) {
        currentInsertState = GomokuQGraphicsItem::State::Black;
        setState(GameState::BlackTurn);
    }

    tryExpand(p);
}

void GomokuQGraphicsScene::tryExpand(QPoint p) {

    QRect tmp(0, 0, boardRect.width(), boardRect.height());

    if( p.y() <= detectExpandSize) {
        for(int i = expandSize - p.y(); i > 0; i--) {
            expandTop();
        }
    }


    if( p.x() <=  detectExpandSize) {
       for(int i = expandSize - p.x(); i > 0; i--) {
           expandLeft();
       }
    }

    if( tmp.height() - p.y() <= detectExpandSize) {
       for(int i = expandSize  - (tmp.height() - p.y()); i > 0; i--) {
            expandBottom();
       }
    }

    if( tmp.width() - p.x() <= detectExpandSize) {
        for(int i =expandSize - tmp.width() +  p.x(); i > 0; i--) {
            expandRight();
        }
    }
}

void GomokuQGraphicsScene::expandTop(){
    boardRect.adjust(0,-1,0,0);
    for (int x = boardRect.left(); x <= boardRect.right(); x++) {
        auto *item = addRect(x, boardRect.top(), 1, 1, gridPen);
        item->setParentItem(grid);
    }
    board.insert(board.begin(), std::vector<GomokuQGraphicsItem*>(boardRect.width()+1, nullptr));

}

void GomokuQGraphicsScene::expandBottom() {
    boardRect.adjust(0,0,0,1);
    for (int x = boardRect.left(); x <= boardRect.right(); x++) {
        auto *item = addRect(x, boardRect.bottom(), 1, 1, gridPen);
        item->setParentItem(grid);
    }
    board.push_back(std::vector<GomokuQGraphicsItem*>(boardRect.width()+1, nullptr));
}

void GomokuQGraphicsScene::expandLeft(){
    boardRect.adjust(-1,0,0,0);
    for (int y = boardRect.top(); y <= boardRect.bottom();y++) {
        auto *item = addRect(boardRect.left(), y, 1, 1, gridPen);
        item->setParentItem(grid);
    }

    for(auto &vec: board) {
        vec.insert(vec.begin(), nullptr);
    }
}
void GomokuQGraphicsScene::expandRight(){
    boardRect.adjust(0,0,1,0);
    for (int y = boardRect.top(); y <= boardRect.bottom();y++) {
        auto *item = addRect(boardRect.right(), y, 1, 1, gridPen);
        item->setParentItem(grid);
    }
    for(auto &vec: board) {
        vec.push_back(nullptr);
    }
}

bool GomokuQGraphicsScene::tryWin(int x, int y) {
    Directions dirs(x, y);

    for(auto& dir: dirs.arr) {
        if(countDir(dir) == stonesToWin) {
            markAsWin(dir);
            if(gameState == GameState::BlackTurn) {
                setState(GameState::BlackWins);
            }
            else {
               setState(GameState::WhiteWins);
            }
            return true;
        }
    }

    return false;
}


int GomokuQGraphicsScene::countDir(Direction &dir) {
    countDirBackward(dir);
    countDirForward(dir);
    return dir.count;
}

int GomokuQGraphicsScene::countDirBackward(Direction &dir) {
    int x = dir.start.x;
    int y = dir.start.y;

    while(sameState(x+dir.moveXBackward, y + dir.moveYBackward))
    {
        x+=dir.moveXBackward,
        y+=dir.moveYBackward,
        dir.count++;
    }

    dir.start.x = x;
    dir.start.y = y;
    return dir.count;
}

int GomokuQGraphicsScene::countDirForward(Direction &dir) {
    while(sameState(dir.end.x, dir.end.y)) {
        dir.count++;
        dir.end.x += dir.moveXForward;
        dir.end.y += dir.moveYForward;
    }
    return dir.count;
}


bool GomokuQGraphicsScene::inBoard(int x, int y) {
    return x <= boardRect.width()
           && y <= boardRect.height()
           && x >= 0
           && y >= 0;
}

bool GomokuQGraphicsScene::sameState(int x, int y) {
    return inBoard(x, y) && board[y][x] != nullptr && board[y][x]->state == currentInsertState;
}

void GomokuQGraphicsScene::markAsWin(Direction &dir) {
    for(int x = dir.start.x, y = dir.start.y;
        x != dir.end.x || y != dir.end.y;
        x+=dir.moveXForward, y+=dir.moveYForward) {
        board[y][x]->state=GomokuQGraphicsItem::State::Winning;
        board[y][x]->update();
    }
}
