#include "board/board.hpp"

Board::Board() 
{
    board.resize(BOARD_SIZE, std::vector<Cell>(BOARD_SIZE, EMPTY));
}

void Board::placeStone(int x, int y, Cell color)
{
    if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE)
        board[y][x] = color;
}

void Board::printBoard() const
{
    for (int y = 0; y < BOARD_SIZE; ++y)
    {
        for (int x = 0; x < BOARD_SIZE; ++x)
        {
            char c = '.';
            if (board[y][x] == BLACK)
                c = 'X';
            else if (board[y][x] == WHITE)
                c = 'O';
            std::cout << c << ' ';
        }
        std::cout << std::endl;
    }
}

bool Board::isPlacementValid(int x, int y)
{
    if (x < 0 || x >= BOARD_SIZE || y < 0 || y >= BOARD_SIZE)
        return (std::cout << "Invalid move : out of bounds" << std::endl, false);
    else if (board[y][x] != EMPTY)
        return (std::cout << "Invalid move : cell occupied" << std::endl, false);
    return true;
}

bool Board::checkWin(Cell color)
{
    int dx[] = {1, 0, 1, -1};
    int dy[] = {0, 1, 1, 1};

    for (int y = 0; y < BOARD_SIZE; ++y) {
        for (int x = 0; x < BOARD_SIZE; ++x) {
            if (board[y][x] != color)
                continue;
            for (int dir = 0; dir < 4; ++dir) {
                int count = 0;
                int nx = x;
                int ny = y;

                for (int i = 0; i < 5; ++i) {
                    if (nx < 0 || nx >= BOARD_SIZE || ny < 0 || ny >= BOARD_SIZE)
                        break;
                    if (board[ny][nx] != color)
                        break;
                    count++;
                    nx += dx[dir];
                    ny += dy[dir];
                }
                if (count >= 5)
                    return true;
            }
        }
    }
    return false;
}