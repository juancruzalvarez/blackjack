#ifndef STRATEGY_H
#define STRATEGY_H

#include "game.h"

class Strategy
{
public:
   virtual int bet(int min, int max) = 0;
   virtual PlayerAction play(Hand player_hand, Card dealer_card, bool can_split, bool can_double, bool can_surrender) = 0;
   virtual bool wants_insurance();
   virtual void see_card(Card card) = 0;
   virtual void see_cards(std::vector<Card> cards) = 0;
   virtual void on_shuffle() = 0;
};

#endif