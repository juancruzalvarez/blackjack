#include "perfect_strategy.h"

#include <array>

namespace blackjack
{

namespace {


}


//time complexity O(n) = 10^n where n is the ammount of cards drawed before hitting at least 16 or busting.
void calculate_dealer_probabilities(Hand dealer_hand, double current_prob, double results[5], std::array<int, 10> cards_left)
{
    if(dealer_hand.Value()>16)
        results[std::min(dealer_hand.Value()-17, 5)] += current_prob;
   for(int c = 2; c<11; c++){
      cards_left[c]--;
      
      cards_left[c]++;
   }

}

double PerfectStrategy::get_doubling_expected_value(Hand player_hand, std::vector<double> dealer_probabilities);
double PerfectStrategy::get_standing_expected_value(Hand player_hand, std::vector<double> dealer_probabilities);
double PerfectStrategy::get_hitting_expected_value(Hand player_hand, std::vector<double> dealer_probabilities);
double PerfectStrategy::get_card_probability(Card c)
{
    double cards_left = 0;
    for(int i = 0; i<10; i++)
        cards_left+=cards_remaining[i];
    return cards_remaining[c]/cards_left;
}
}

int PerfectStrategy::bet(int min, int max)
{
   return min;
}

PlayerAction PerfectStrategy::play(Hand player_hand, Card dealer_card, PlayOptions options)
{
   if(options.can_split && player_hand.CanSplit() && (player_hand.Value() == 16 || player_hand.Value() == 12))
      return PlayerAction::SPLIT;
   
   if(options.can_double && (player_hand.Value() == 11 ||player_hand.Value() == 10))
      return PlayerAction::DOUBLE;
   if (21 - player_hand.Value() <= 6)
      return PlayerAction::STAND;
   else
      return PlayerAction::HIT;
}

bool PerfectStrategy::wants_insurance()
{
   return false;
}

void PerfectStrategy::see_card(Card card) {}
void PerfectStrategy::see_cards(std::vector<Card> cards) {}
void PerfectStrategy::on_shuffle() {}




}