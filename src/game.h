#ifndef GAME_H
#define GAME_H

#include <vector>

#include "shoe.h"
#include "player.h"

const int kMaxPlayersPerTable = 7;

struct Rules
{
   int decks;                        // amount of decks that are shufled together.
   bool dealer_hit_s17;              // does the dealer hit or stands soft 17
   bool can_surrender;               // is the player allowed to surrender their hand.
   bool can_DAS;                     // can the player double after spliting.
   bool bj_3_to_2;                   // blackjack pays 3:2 or 6:5.
   bool allows_insurance;            // if dealer's up card is an ace all players are offered to make insurance bet, pays 2:1
   bool can_hit_after_spliting_aces;
   int max_splits;
   int min_bet, max_bet;             // betting range.
   float penetration_before_shuffle; // what percentaje of the cards are used before the cards are shuffled again.  (0.0 : 1.0)
};

enum class PlayerAction
{
   STAND,
   HIT,
   DOUBLE,
   SPLIT,
   SURRENDER,
};

class Game
{
public:
   Game(Rules rules, std::vector<Player*> players);
   void do_round();
private:
   Rules rules;
   Shoe shoe;
   std::vector<Player*> players;
   int rounds_played;
   int house_profit;
   Card draw_card();
   Round *player_round(Player *player, Hand player_hand, int bet, Card dealer_up, bool can_split, bool can_double, bool can_surrender, int splits_done);
   int dealer_round(Hand dealer_hand);
};


#endif