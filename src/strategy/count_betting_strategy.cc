#include "count_betting_strategy.h"
#include <iostream>
namespace bj
{

   CountBettingStrategy::CountBettingStrategy(
       std::map<Card, double> card_values,
       std::function<int(double, int, int)> calculate_bet_ammount_fn,
       int decks)
   {
      this->card_values = card_values;
      this->calculate_bet_ammount_fn = calculate_bet_ammount_fn;
      this->decks = decks;
      this->cards_seen = 0;
   }

   int CountBettingStrategy::bet(int min_bet, int max_bet)
   {
      double decks_left = decks - cards_seen / double(kCardsPerDeck);
      int true_count = count / decks_left;
      int bet = calculate_bet_ammount_fn(true_count, min_bet, max_bet);
      return bet;
   }

   bool CountBettingStrategy::wants_insurance()
   {
      return false;
   }

   void CountBettingStrategy::see_card(Card card)
   {
      cards_seen++;
      count += card_values[card];
   }

   void CountBettingStrategy::see_cards(std::vector<Card> cards)
   {
      for (const auto &c : cards)
      {
         count += card_values[c];
         cards_seen++;
      }
   }

   void CountBettingStrategy::on_shuffle(int decks)
   {
      count = 0;
      cards_seen = 0;
   }

   namespace count
   {

      int basic_betting(double count, int min_bet, int max_bet)
      {
         return std::max(count - 1, 1.0) * min_bet;
      }
   }

}