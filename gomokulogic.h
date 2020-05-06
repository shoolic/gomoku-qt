//#ifndef GOMOKULOGIC_H
//#define GOMOKULOGIC_H

//#include <array>
//class GomokuLogic
//{
//public:
//    GomokuLogic();

//    enum class CellState {
//        Empty,
//        Black,
//        White
//    };

//    enum class GameState {
//        BlackTurn,
//        WhiteTurn,
//        BlackWins,
//        WhiteWins
//    };

//    std::array<std::array<CellState,15>,15> board;
//    GameState gameState;

//    struct Cell {
//        int x;
//        int y;
//        Cell(int x, int y): x(x), y(y) {}
//    };

//    struct Direction {
//        Cell start;
//        Cell end;
//        int count;
//        int moveX;
//        int moveY;
//        Direction(int x, int y, int moveX, int moveY): start(x,y), end(x,y),
//            count(0), moveX(moveX), moveY(moveY) {}
//    };

//    struct Directions {
//        Direction vertical;
//        Direction horizontal;
//        Direction diagonalNW;
//        Direction diagonalNE;
//        Directions(int x, int y):
//            vertical(x,y, 0, 1), horizontal(x,y, 1, 0), diagonalNW(x,y, 1, 1), diagonalNE(x,y, -1, 1) {}
//    };


//    void checkForWin(int x, int y) {
//        Directions dirs(x, y);
//        CellState currentTurnCellState;

//    }

//    bool checkVertical(Direction &dir) {
//        while(board[dir.start.x][dir.start.y] == currentTurnCellState) {
//            dir.count++;
//            dir.start.y++;
//        }
//        while(board[dir.end.x][dir.end.y] == currentTurnCellState) {
//            dir.count++;
//            dir.end.y--;
//        }

//        if(dir.count == 5) {
//            return true;
//        }

//        return false;
//    }

//    bool checkHorizontal(Direction &dir) {
//        while(board[dir.start.x][dir.start.y] == currentTurnCellState) {
//            dir.count++;
//            dir.start.y--;
//        }
//        while(board[dir.end.x][dir.end.y] == currentTurnCellState) {
//            dir.count++;
//            dir.end.y++;
//        }

//        if(dir.count == 5) {
//            return true;
//        }

//        return false;
//    }

//    bool checkDiagonalNW(Direction &dir) {
//        while(board[dir.start.x][dir.start.y] == currentTurnCellState) {
//            dir.count++;
//            dir.start.x--;
//            dir.start.y--;
//        }

//        while(board[dir.end.x][dir.end.y] == currentTurnCellState) {
//            dir.count++;
//            dir.start.x++;
//            dir.start.y++;
//        }

//        if(dir.count == 5) {
//            return true;
//        }

//        return false;
//    }

//    bool checkDiagonalNE(Direction &dir) {
//        while(board[dir.start.x][dir.start.y] == currentTurnCellState) {
//            dir.count++;
//            dir.start.x++;
//            dir.start.y--;
//        }
//        while(board[dir.end.x][dir.end.y] == currentTurnCellState) {
//            dir.count++;
//            dir.start.x--;
//            dir.start.y++;
//        }

//        if(dir.count == 5) {
//            return true;
//        }

//        return false;
//    }

//};

//#endif // GOMOKULOGIC_H
