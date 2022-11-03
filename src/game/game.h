#ifndef GAME_H
#define GAME_H

#include <vector>

#include "round.h"
#include "rules.h"
#include "shoe.h"
#include "player.h"
#include "player_action.h"

namespace bj
{

   const int kMaxPlayersPerTable = 7;

   

   class Game
   {
   public:
      Game(Rules rules, std::vector<Player*> players);
      void DoRound();

   private:
      Round *DoPlayerRound(Player *player, Hand player_hand, Card dealer_up, PlayOptions options);
      int DoDealerRound(Hand dealer_hand);
      Card DrawCard();
      std::vector<Player *> players;
      Rules rules;
      Shoe shoe;
      int rounds_played;
      int house_profit;
   };

}

#endif
