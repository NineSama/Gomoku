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
            if (!board.isPlacementValid(gridX, gridY))
                continue;
            drawGrid(ui);
            board.placeStone(gridX, gridY, current->color);
            current->captures += board.checkCapture(gridX, gridY, current->color);
            board.printBoard();
            drawBoard(ui, board);
            if (board.checkWin(current->color))
                return (std::cout << (current->color == BLACK ? "Black" : "White") << " wins by 5 in a row!" << std::endl, 1);
            if (winByCapture(*current))
                return (std::cout << (current->color == BLACK ? "Black" : "White") << " wins by capture!" << std::endl, 1);
            current = (current->color == BLACK ? &white : &black);
        }
    }

    XCloseDisplay(ui.display);
    return 0;
}
