#include <iostream>
#include "board/board.hpp"

int main()
{
    Board board;

    Cell currentPlayer = BLACK;
    int x, y;
    
    board.printBoard();

    while (true)
    {
        std::cout << (currentPlayer == BLACK ? "Black" : "White")
            << " to move (input [x] [y]) : ";
        std::cin >> x >> y;
        
        if (!board.isPlacementValid(x, y))
            continue;

        board.placeStone(x, y, currentPlayer);
        board.printBoard();
        if (board.checkWin(currentPlayer))
            return (std::cout << (currentPlayer == BLACK ? "Black" : "White") << " has won!" << std::endl, 1);
        currentPlayer = (currentPlayer == BLACK ? WHITE : BLACK);
    }

    return 0;
}
