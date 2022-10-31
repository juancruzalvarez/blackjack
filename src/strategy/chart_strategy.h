#ifndef CHART_STRATEGY_H
#define CHART_STRATEGY_H

#include "strategy.h"

namespace blackjack {

class ChartStrategy : public Strategy {

public:
   int bet(int min, int max);
   PlayerAction play(Hand player_hand, Card dealer_card, bool can_split, bool can_double, bool can_surrender);
   bool wants_insurance();
   void see_card(Card card);
   void see_cards(std::vector<Card> cards);
   void on_shuffle();
private:
   enum class ChartAction {
      
   }
};

}


#endif