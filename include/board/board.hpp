#ifndef BOARD_HPP
#define BOARD_HPP

#include <vector>
#include <iostream>
#include "board/cell.hpp"
#include "utils/utils.hpp"
#include "player.hpp"

const int BOARD_SIZE = 19;

struct Position
{
    int x;
    int y;
};

class Board
{
    private:
        std::vector<std::vector<Cell> > board;

    public:
        Board();

        void printBoard() const;

        void    placeStone(int x, int y, Cell color);
        void    removeStone(int x, int y);
        bool    isPlacementValid(int x, int y);
        bool    isInside(int x, int y) const;
        bool    hasNeighbor(int x, int y, int maxDist) const;
        bool    checkWin(Cell color);
        bool    isGameOver();
        bool    isPairCapturable(int x, int y, int dir, Cell color);
        bool    isDoubleFreeThree(int x, int y, Cell color);
        int     checkCapture(int x, int y, Cell color);
        std::vector<std::vector<Cell> > getBoard() const;
        Cell getCell(int x, int y) const;
        std::vector<Cell> getRow(int y) const;
        std::vector<Cell> getColumn(int x) const;

};

#endif
