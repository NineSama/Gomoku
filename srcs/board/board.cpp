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

int Board::checkCapture(int x, int y, Cell color)
{
    Cell opponent = (color == BLACK) ? WHITE : BLACK;

    int dx[] = {1, 1, 0, -1, -1, -1, 0, 1};
    int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};
    int count = 0;

    for (int dir = 0; dir < 8; ++dir) {
        int nx1 = x + dx[dir];
        int ny1 = y + dy[dir];
        int nx2 = x + 2 * dx[dir];
        int ny2 = y + 2 * dy[dir];
        int nx3 = x + 3 * dx[dir];
        int ny3 = y + 3 * dy[dir];

        if (nx3 < 0 || nx3 >= BOARD_SIZE || ny3 < 0 || ny3 >= BOARD_SIZE)
            continue;
        if (board[ny1][nx1] == opponent && board[ny2][nx2] == opponent && board[ny3][nx3] == color)
        {
            board[ny1][nx1] = EMPTY;
            board[ny2][nx2] = EMPTY;
            count++;
            std::cout << (color == BLACK ? "Black" : "White") << " captures at [" << nx1 << ", " << ny1 << "] and [" << nx2 << ", " << ny2 << "]" << std::endl;
        }
    }
    return count;
}