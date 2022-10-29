#ifndef GAME_H
#define GAME_H

#include <vector>

#include "player.h"

// in blackjack, the suit of the card is irelevant
// 1 represents ace, 10 represents all face cards(J, Q, K), and the rest are represented by their number.
typedef int Card;

const Card DECK[] = {1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,7,8,8,8,8,9,9,9,9,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10};

struct Rules
{
   int decks;           // amount of decks that are shufled together.
   bool dealer_hit_s17; // does the dealer hit or stands soft 17
   bool can_surrender;  // is the player allowed to surrender their hand.
   bool can_DAS;
   bool bj_3_to_2; // blackjack pays 3 to 2 or 6 to 5
   int min_bet, max_bet;
   float percentaje_before_shuffle; // what percentaje of the cards are used before the cards are shuffled again.  (0.0 : 1.0)
};

enum class PlayerAction
{
   STAND,
   HIT,
   DOUBLE,
   SPLIT,
   SURRENDER,
};

struct Game
{
   Rules rules;
   std::vector<Card> cards;
   std::vector<Player*> players;
   int hands_played;
   int profit;
};

std::vector<Card> shuffle(int decks);
Game new_game(Rules rules, std::vector<Player> players);
void do_hand(Game &game);

#endif