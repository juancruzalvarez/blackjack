#include "min_betting_strategy.h"

namespace bj {

int MinBettingStrategy::bet(int min_bet, int max_bet)
{
    return min_bet;
}

bool MinBettingStrategy::wants_insurance()
{
    return false;
}

void MinBettingStrategy::see_card(Card card){}

void MinBettingStrategy::see_cards(std::vector<Card> cards){}

void MinBettingStrategy::on_shuffle(int decks){}

}