#include "board/board.hpp"

Board::Board()
{
    board.resize(BOARD_SIZE, std::vector<Cell>(BOARD_SIZE, EMPTY));
}

void Board::placeStone(int x, int y, Cell color)
{
    if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {
        board[y][x] = color;
        // std::cout << (color == BLACK ? "Black" : "White") << " places stone at [" << x << ", " << y << "]" << std::endl;
    }
}

void Board::removeStone(int x, int y)
{
    if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE)
        board[y][x] = EMPTY;
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
    if (!isInside(x, y)) {
        // std::cout << "Invalid move : out of bounds" << std::endl;
        return false;
    }
    else if (board[y][x] != EMPTY) {
        // std::cout << "Invalid move : cell occupied" << std::endl;
        return false;
    }
    return true;
}

bool Board::isInside(int x, int y) const
{
    return (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE);
}

bool Board::hasNeighbor(int x, int y, int maxDist) const
{
    for (int dy = -maxDist; dy <= maxDist; dy++) {
        for (int dx = -maxDist; dx <= maxDist; dx++) {
            if (dy == 0 && dx == 0)
                continue;
            if (!isInside(x + dx, y + dy))
                continue;
            if (board[y + dy][x + dx] != EMPTY)
                return true;
        }
    }
    return false;
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
                while (nx >= 0 && nx < BOARD_SIZE && ny >= 0 && ny < BOARD_SIZE && board[ny][nx] == color) {
                    count++;
                    nx += dx[dir];
                    ny += dy[dir];
                }
                if (count >= 5)
                    if (!isPairCapturable(nx - dx[dir], ny - dy[dir], dir, color))
                        return true;
            }
        }
    }
    return false;
}

bool Board::isGameOver()
{
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            if (board[y][x] != EMPTY) {
                if (checkWin(board[y][x]))
                    return true;
            }
        }
    }
    return false;
}

bool Board::isPairCapturable(int x, int y, int rowDir, Cell color)
{
    Cell opponent = (color == BLACK) ? WHITE : BLACK;

    int dx[] = {1, 0, 1, -1, -1, 0, -1, 1};
    int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};

    while (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {
        for (int dir = 0; dir < 8; ++dir) {
            int nx0 = x - dx[dir];
            int ny0 = y - dy[dir];
            int nx1 = x + dx[dir];
            int ny1 = y + dy[dir];
            int nx2 = x + 2 * dx[dir];
            int ny2 = y + 2 * dy[dir];
            if (!isInside(nx0, ny0) || !isInside(nx1, ny1) || !isInside(nx2, ny2))
                continue;
            if (board[ny0][nx0] == opponent && board[ny1][nx1] == color && board[ny2][nx2] == EMPTY)
                return (std::cout << "Pair is capturable at [" << nx2 << ", " << ny2 << "]" << std::endl, true);
        }
        x -= dx[rowDir];
        y -= dy[rowDir];
    }
    return false;
}

bool Board::isDoubleFreeThree(int x, int y, Cell color)
{
    int dx[] = {1, 0, 1, -1};
    int dy[] = {0, 1, 1, 1};
    std::string lineStr;
    int count = 0;
    std::vector<std::vector<Cell> > tempBoard = board; // Create a temporary copy of the board
    tempBoard[y][x] = color; // Place the stone on the temporary board

    for (int dir = 0; dir < 4; ++dir) {
        std::vector<Cell> line;
        for (int i = -4; i <= 4; ++i) {
            int nx = x + i * dx[dir];
            int ny = y + i * dy[dir];
            if (isInside(nx, ny))
                line.push_back(tempBoard[ny][nx]);
            else
                line.push_back(color == BLACK ? WHITE : BLACK); // Treat out of bounds as opponent color
        }
        std::string lineStr;
        lineStr.reserve(9);
        for (size_t i = 0; i < line.size(); ++i) {
            lineStr += cellToChar(line[i], color);
        }
        if (createsFreeThree(lineStr))
            count++;
        std::cout << "Line " << dir << ": " << lineStr << std::endl;

    }
    return count >= 2; // Return true if there are at least two free threes
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

std::vector<std::vector<Cell> > Board::getBoard() const
{return board;}

Cell Board::getCell(int x, int y) const
{
    if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE)
        return board[y][x];
    return EMPTY;
}

std::vector<Cell> Board::getRow(int y) const
{
    if (y >= 0 && y < BOARD_SIZE)
        return board[y];
    return std::vector<Cell>();
}

std::vector<Cell> Board::getColumn(int x) const
{
    if (x >= 0 && x < BOARD_SIZE) {
        std::vector<Cell> column;
        for (int y = 0; y < BOARD_SIZE; y++) {
            column.push_back(board[y][x]);
        }
        return column;
    }
    return std::vector<Cell>();
}
