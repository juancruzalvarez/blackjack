#ifndef PLAYER_H
#define PLAYER_H

#include "../strategy/strategy.h"
#include "../strategy/betting_strategy.h"


namespace bj {

class Player
{
public:
   Player(int starting_chips, Strategy *strategy, BettingStrategy *betting_strategy);
   PlayerAction Play(Hand player_hand, Card dealer_card, PlayOptions options);
   int Bet(int min, int max);
   bool WantsInsurance();
   void SeeCard(Card card);
   void SeeCards(std::vector<Card> cards);
   void OnShuffle(int decks);
   void AddChips(int chips);
   int CurrentChips();
   int StartingChips();

private:
   Strategy *strategy;
   BettingStrategy *betting_strategy;
   int starting_chips;
   int current_chips;
  
};

}

#endif