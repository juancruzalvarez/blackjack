#include "basic_strategy.h"

namespace bj
{

int BasicStrategy::bet(int min, int max)
{
   return min;
}

PlayerAction BasicStrategy::play(Hand player_hand, Card dealer_card, PlayOptions options)
{
   if (21 - player_hand.Value() <= 6)
      return PlayerAction::STAND;
   else
      return PlayerAction::HIT;
}

bool BasicStrategy::wants_insurance()
{
   return false;
}

void BasicStrategy::see_card(Card card) {}
void BasicStrategy::see_cards(std::vector<Card> cards) {}
void BasicStrategy::on_shuffle(int decks) {}

}