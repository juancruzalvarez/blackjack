#ifndef PLAYER_H
#define PLAYER_H

#include "../strategy/strategy.h"

namespace bj {

struct Player
{
   int starting_chips;
   int current_chips;
   Strategy *strategy;
};

}

#endif