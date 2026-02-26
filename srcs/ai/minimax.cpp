#include "ai/minimax.hpp"

Position findBestMove(Board& board, Player& ai, int depth)
{
    std::vector<Position> moves = generateMove(board);
    Position bestMove = {-1, -1};
    int bestScore = std::numeric_limits<int>::min();
    for (size_t i = 0; i < moves.size(); ++i) {
        Position pos = moves[i];
        board.placeStone(pos.x, pos.y, ai.color);
        int score = minimax(board, depth, false, ai);
        board.removeStone(pos.x, pos.y);
        if (score > bestScore) {
            bestScore = score;
            bestMove = pos;
        }
    }
    return bestMove;
}

int minimax(Board& board, int depth, bool maximizingPlayer, Player& player)
{
    if (depth == 0 || board.isGameOver()) {
        return evaluateBoard(board, player.color);
    }
    std::vector<Position> moves = generateMove(board);
    if (maximizingPlayer) {
        int maxEval = std::numeric_limits<int>::min();
        for (size_t i = 0; i < moves.size(); ++i) {
            Position pos = moves[i];
            board.placeStone(pos.x, pos.y, player.color);
            int eval = minimax(board, depth - 1, false, player);
            board.removeStone(pos.x, pos.y);
            maxEval = std::max(maxEval, eval);
        }
        return maxEval;
    }
    else {
        int minEval = std::numeric_limits<int>::max();
        Cell opponent = (player.color == BLACK) ? WHITE : BLACK;
        for (size_t i = 0; i < moves.size(); ++i) {
            Position pos = moves[i];
            board.placeStone(pos.x, pos.y, opponent);
            int eval = minimax(board, depth - 1, true, player);
            board.removeStone(pos.x, pos.y);
            minEval = std::min(minEval, eval);
        }
        return minEval;
    }
}

std::vector<Position> generateMove(Board& board)
{
    std::vector<Position> moves;
    for (int x = 0; x < BOARD_SIZE; ++x) {
        for (int y = 0; y < BOARD_SIZE; ++y) {
            if (board.hasNeighbor(x, y, 2) && board.isPlacementValid(x, y)) {
                Position pos;
                pos.x = x;
                pos.y = y;
                moves.push_back(pos);
            }
        }
    }
    if (moves.empty()) {
        Position pos;
        pos.x = 9;
        pos.y = 9;
        moves.push_back(pos);
    }
    return moves;
}