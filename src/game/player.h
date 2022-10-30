#ifndef PLAYER_H
#define PLAYER_H

#include "../strategy/strategy.h"

namespace blackjack {

struct Player
{
   int starting_chips;
   int current_chips;
   Strategy *strat;
};

}

#endif