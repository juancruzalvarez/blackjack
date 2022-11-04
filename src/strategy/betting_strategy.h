#ifndef BETTING_STRATEGY_H
#define BETTING_STRATEGY_H

#include <vector>

#include "../game/card.h"

namespace bj {

class BettingStrategy
{
    
public:
    virtual int bet(int min, int max) = 0;
    virtual bool wants_insurance() = 0;
    virtual void see_card(Card card) = 0;
    virtual void see_cards(std::vector<Card> cards) = 0;
    virtual void on_shuffle(int decks) = 0;

};

}


#endif