#include <iostream>
#include <limits>
#include "board/board.hpp"
#include "player.hpp"
#include "utils/utils.hpp"

int main()
{
    Board board;
    Player black = {BLACK, 0};
    Player white = {WHITE, 0};

    Player* current = &black;
    int x, y;
    
    board.printBoard();

    while (true)
    {
        std::cout << (current->color == BLACK ? "Black" : "White")
            << " to move (input [x] [y]) : ";
        std::cin >> x >> y;
        if (std::cin.fail())
        {
            std::cin.clear(); // Clear error state
            std::cout << "Invalid input : Please enter two integers." << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
            continue;
        }

        if (!board.isPlacementValid(x, y))
            continue;

        board.placeStone(x, y, current->color);
        current->captures += board.checkCapture(x, y, current->color);
        board.printBoard();
        if (board.checkWin(current->color))
            return (std::cout << (current->color == BLACK ? "Black" : "White") << " wins by 5 in a row!" << std::endl, 1);
        if (winByCapture(*current))
            return (std::cout << (current->color == BLACK ? "Black" : "White") << " wins by capture!" << std::endl, 1);
        current = (current->color == BLACK ? &white : &black);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
    }

    return 0;
}
