#ifndef HEURISTICS_HPP
#define HEURISTICS_HPP

#include "board/board.hpp"

int scoreSequence(int length, int openEnds);
int evaluateLine(const std::vector<Cell>& line, Cell color);
int evaluatePlayer(const Board& board, Cell color);
int evaluateBoard(const Board& board, Cell color);

#define HEURISTICS_HPP