#include "player.hpp"
#include "utils/utils.hpp"

bool winByCapture(const Player& player)
{
    if (player.captures >= 5)
        return true;
    return false;
}

char cellToChar(Cell cell, Cell current)
{
    if (cell == EMPTY)
        return '.';
    else if (cell == current)
        return 'X';
    else
        return 'O'; 
}

bool createsFreeThree(const std::string& line)
{
    if (line.find(".XXX.") != std::string::npos)
        return true;
    else if (line.find(".X.XX.") != std::string::npos)
        return true;
    else if (line.find(".XX.X.") != std::string::npos)
        return true;
    return false;
}