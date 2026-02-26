#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "board/cell.hpp"

struct Player
{
    Cell color;
    int captures;
};

#endif