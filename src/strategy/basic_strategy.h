#ifndef BASIC_STRATEGY_H
#define BASIC_STRATEGY_H

#include "strategy.h"

namespace blackjack {
class BasicStrategy : public Strategy {
   
public:
   int bet(int min, int max);
   PlayerAction play(Hand player_hand, Card dealer_card, PlayOptions options);
   bool wants_insurance();
   void see_card(Card card);
   void see_cards(std::vector<Card> cards);
   void on_shuffle();
};

}

#endif