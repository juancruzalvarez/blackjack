#ifndef PERFECT_STRATEGY
#define PERFECT_STRATEGY

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
    void on_shuffle();
private:
    int cards_remaining[10];
    std::vector<double> get_dealer_probabilities(Card dealer_card); 
    double get_doubling_expected_value(Hand player_hand, std::vector<double> dealer_probabilities);
    double get_standing_expected_value(Hand player_hand, std::vector<double> dealer_probabilities);
    double get_hitting_expected_value(Hand player_hand, std::vector<double> dealer_probabilities);
    double get_card_probability(Card c);
};

}

#endif