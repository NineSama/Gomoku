#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include "player.hpp"
#include "board/cell.hpp"

bool winByCapture(const Player& player);
char cellToChar(Cell cell, Cell current);
bool createsFreeThree(const std::string& line);

#endif