#ifndef MIN_BETTING_STRATEGY_H
#define MIN_BETTING_STRATEGY_H

#include "betting_strategy.h"

namespace bj {

class MinBettingStrategy : public BettingStrategy {
public:
    int bet(int min, int max);
    bool wants_insurance();
    void see_card(Card card);
    void see_cards(std::vector<Card> cards);
    void on_shuffle(int decks);
};

}

#endif