#ifndef CHART_STRATEGY_H
#define CHART_STRATEGY_H

#include "strategy.h"
#include "chart.h"

namespace bj {

class ChartStrategy : public Strategy {

public:
   ChartStrategy(Chart chart);
   int bet(int min, int max);
   PlayerAction play(Hand player_hand, Card dealer_card, PlayOptions options);
   bool wants_insurance();
   void see_card(Card card);
   void see_cards(std::vector<Card> cards);
   void on_shuffle(int decks);
private:
   Chart chart;
};

}


#endif