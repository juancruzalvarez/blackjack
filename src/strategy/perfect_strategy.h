#ifndef PERFECT_STRATEGY
#define PERFECT_STRATEGY

#include <array>

#include "strategy.h"

namespace blackjack {

class PerfectStrategy : public Strategy {
public:
    PerfectStrategy(int deck_count);
    int bet(int min, int max);
    PlayerAction play(Hand player_hand, Card dealer_card, PlayOptions options);
    bool wants_insurance();
    void see_card(Card card);
    void see_cards(std::vector<Card> cards);
    void on_shuffle(int decks);
private:
    std::array<int, 10> cards_left;
};

}

#endif