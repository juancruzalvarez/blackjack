#ifndef COUNT_BETTING_STRATEGY_H
#define COUNT_BETTING_STRATEGY_H

#include <map>
#include <functional>

#include "betting_strategy.h"

namespace bj {

class CountBettingStrategy : public BettingStrategy {
public:
    CountBettingStrategy(
        std::map<Card, double> card_values,
        std::function<int(double, int, int)> calculate_bet_ammount_fn,
        int decks
    );
    int bet(int min, int max);
    bool wants_insurance();
    void see_card(Card card);
    void see_cards(std::vector<Card> cards);
    void on_shuffle(int decks);
private:
    std::function<int(double, int, int)> calculate_bet_ammount_fn;
    std::map<Card, double> card_values;
    double count;
    int decks;
    int cards_seen;
};

namespace count {
    const std::map<Card, double> kHiLoValues = {
        {2,1},
        {3,1},
        {4,1},
        {5,1},
        {6,1},
        {7,0},
        {8,0},
        {9,0},
        {10,-1},
        {11,-1},
    };

    const std::map<Card, double> kHiOpIIValues = {
        {2,1},
        {3,1},
        {4,2},
        {5,2},
        {6,1},
        {7,1},
        {8,0},
        {9,0},
        {10,-2},
        {11,0},
    };

    int basic_betting(double count, int min_bet, int max_bet);
}

}

#endif