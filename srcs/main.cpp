#include <iostream>
#include <limits>
#include "board/board.hpp"
#include "player.hpp"
#include "utils/utils.hpp"
#include "ui/init_ui.hpp"

int main()
{
    Board board;
    Player black = {BLACK, 0};
    Player white = {WHITE, 0};

    Player* current = &black;

    UIData ui = initUI();
    XEvent event;
    
    board.printBoard();
    
    while (true)
    {
        XNextEvent(ui.display, &event);
        if (event.type == Expose)
            drawGrid(ui);
        else if (event.type == ButtonPress) {
            int gridX, gridY;
            if (!clickCoordinates(event.xbutton.x, event.xbutton.y, gridX, gridY))
                continue;
            // std::cout << (current->color == BLACK ? "Black" : "White")
            //     << " to move (input [x] [y]) : ";
            // std::cin >> x >> y;
            // if (std::cin.fail())
            // {
            //     std::cin.clear(); // Clear error state
            //     std::cout << "Invalid input : Please enter two integers." << std::endl;
            //     std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
            //     continue;
            // }

            if (!board.isPlacementValid(gridX, gridY))
                continue;
            drawGrid(ui);
            board.placeStone(gridX, gridY, current->color);
            // drawStone(ui, gridX, gridY, current->color == BLACK ? getColor(ui.display, "#000000") : getColor(ui.display, "#FFFFFF"));
            current->captures += board.checkCapture(gridX, gridY, current->color);
            board.printBoard();
            drawBoard(ui, board);
            if (board.checkWin(current->color))
                return (std::cout << (current->color == BLACK ? "Black" : "White") << " wins by 5 in a row!" << std::endl, 1);
            if (winByCapture(*current))
                return (std::cout << (current->color == BLACK ? "Black" : "White") << " wins by capture!" << std::endl, 1);
            current = (current->color == BLACK ? &white : &black);
            // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
        }
    }

    XCloseDisplay(ui.display);
    return 0;
}
