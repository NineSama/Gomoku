#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <iostream>

const int BOARD_SIZE = 19;

enum Cell { EMPTY = 0, BLACK = 1, WHITE = 2 };

class Board
{
    public:
        Board();

        void printBoard() const;

        void    placeStone(int x, int y, Cell color);
        bool    isPlacementValid(int x, int y);
        bool    isInside(int x, int y) const;
        bool    checkWin(Cell color);
        bool    isPairCapturable(int x, int y, int dir, Cell color);
        int     checkCapture(int x, int y, Cell color);

    private:
        std::vector<std::vector<Cell> > board;
};

#endif
