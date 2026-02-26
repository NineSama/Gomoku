#include "ai/heuristics.hpp"

int scoreSequence(int length, int openEnds)
{
    if (length >= 5)
        return 1000000; // Winning sequence
    else if (length == 4) {
        if (openEnds == 2)
            return 10000; // Open four
        else if (openEnds == 1)
            return 1000; // Closed four
    }
    else if (length == 3) {
        if (openEnds == 2)
            return 1000; // Open three
        else if (openEnds == 1)
            return 100; // Closed three
    }
    else if (length == 2) {
        if (openEnds == 2)
            return 100; // Open two
        else if (openEnds == 1)
            return 10; // Closed two
    }
    return 0;
}

int evaluateLine(const std::vector<Cell>& line, Cell color)
{
    int score = 0;
    int length = 0;

    for (int i = 0; i < BOARD_SIZE; ++i) {
        if (line[i] == color) {
            length++;
        }
        else {
            if (length > 0) {
                int openEnds = 0;
                if (i - length - 1 >= 0 && line[i - length - 1] == EMPTY)
                    openEnds++;
                if (i < BOARD_SIZE && line[i] == EMPTY)
                    openEnds++;
                score += scoreSequence(length, openEnds);
                length = 0;
            }
            
        }
    }
    // Check for sequence at the end of the line
    if (length > 0) {
        int openEnds = 0;
        if (BOARD_SIZE - length - 1 >= 0 && line[BOARD_SIZE - length - 1] == EMPTY)
            openEnds++;
        score += scoreSequence(length, openEnds);
    }
    return score;
}

int evaluatePlayer(const Board& board, Cell color)
{
    int score = 0;

    // rows
    for (int y = 0; y < 19; y++)
        score += evaluateLine(board.getRow(y), color);
    // columns
    for (int x = 0; x < 19; x++)
        score += evaluateLine(board.getColumn(x), color);
    // diagonals
    for (int k = 0; k < 19; k++) {
        std::vector<Cell> diagonal;
        for (int x = 0, y = k; x < 19 && y < 19; x++, y++)
            diagonal.push_back(board.getCell(x, y));
        score += evaluateLine(diagonal, color);
    }
    for (int k = 1; k < 19; k++) {
        std::vector<Cell> diagonal;
        for (int x = k, y = 0; x < 19 && y < 19; x++, y++)
            diagonal.push_back(board.getCell(x, y));
        score += evaluateLine(diagonal, color);
    }
    for (int k = 0; k < 19; k++) {
        std::vector<Cell> diagonal;
        for (int x = 0, y = k; x < 19 && y >= 0; x++, y--)
            diagonal.push_back(board.getCell(x, y));
        score += evaluateLine(diagonal, color);
    }
    for (int k = 1; k < 19; k++) {
        std::vector<Cell> diagonal;
        for (int x = k, y = 18; x < 19 && y >= 0; x++, y--)
            diagonal.push_back(board.getCell(x, y));
        score += evaluateLine(diagonal, color);
    }
    return score;
}

int evaluateBoard(const Board& board, Cell color)
{
    int playerScore = evaluatePlayer(board, color);
    int opponentScore = evaluatePlayer(board, (color == BLACK) ? WHITE : BLACK);
    return playerScore - opponentScore;
}