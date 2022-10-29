#ifndef PLAYER_H
#define PLAYER_H

#include "strategy.h"

struct Player
{
   int starting_chips;
   int current_chips;
   Strategy *strat;
};

#endif