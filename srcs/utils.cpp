#include "player.hpp"
#include "utils/utils.hpp"

bool winByCapture(const Player& player)
{
    if (player.captures >= 5)
        return true;
    return false;
}