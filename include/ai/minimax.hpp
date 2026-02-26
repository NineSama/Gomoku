#ifndef MINIMAX_HPP
#define MINIMAX_HPP

#include <limits>
#include "board/board.hpp"
#include "ai/heuristics.hpp"
#include "player.hpp"

Position findBestMove(Board& board, Player& player, int depth);
int minimax(Board& board, int depth, bool maximizingPlayer, Player& player);
std::vector<Position> generateMove(Board& board);

#endif