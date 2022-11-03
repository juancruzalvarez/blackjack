#include "improved_basic_strategy.h"

namespace bj
{

int ImprovedBasicStrategy::bet(int min, int max)
{
   return min;
}

PlayerAction ImprovedBasicStrategy::play(Hand player_hand, Card dealer_card, PlayOptions options)
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

bool ImprovedBasicStrategy::wants_insurance()
{
   return false;
}

void ImprovedBasicStrategy::see_card(Card card) {}
void ImprovedBasicStrategy::see_cards(std::vector<Card> cards) {}
void ImprovedBasicStrategy::on_shuffle(int decks) {}

}