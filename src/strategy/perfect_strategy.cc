#include "perfect_strategy.h"

#include <array>
#include <iostream>

namespace blackjack
{

namespace {

// Given a vector of pairs <action, EV of action>, returns the pair of higher EV.
std::pair<PlayerAction, double> get_max_value_action(std::vector<std::pair<PlayerAction, double>> evs)
{
   auto max_pair = evs[0];
   for(const auto& p : evs)
      max_pair = p.second > max_pair.second ? p : max_pair;
   return max_pair;
}

// Returns the probability when drawing a card from the shoe with @cards_lefts cards in it, of it being @c.
double get_card_probability(blackjack::Card c, std::array<int, 10> cards_left)
{
   if(cards_left[c - 2] <= 0)
      return 0;
   double total_cards_left = 0;
   for (const auto &l : cards_left)
      total_cards_left += l;
   return cards_left[c - 2] / total_cards_left;
}

// Recursivly calculates the probabilities of the dealers possible results
// Stores the results on the @results array.
// The dealer can only have 6 results: 17, 18, 19, 20, 21, BUST
// The first call to the function should have 
// @dealer_hand be a hand with the dealers up card in it,
// @current_prob = 1,
// @results = {0.0,0.0,0.0,0.0,0.0,0.0}
// O(n) = 10^n where n is the ammount of cards drawed before hitting at least 16 or busting.
void calculate_dealer_probabilities(
   blackjack::Hand dealer_hand,
   double current_prob,
   std::array<double, 6> &results,
   std::array<int, 10> cards_left)
{
   // If the current hand has a value of at least 16 the dealer stops drawing.
   // TODO: dealer hits s17
   if (dealer_hand.Value() > 16)
   {
      results[std::min(dealer_hand.Value() - 17, 5)] += current_prob;
      return;
   }

   for (int c = 2; c <= 11; c++)
   {
      if (cards_left[c - 2] > 0)
      {
         double probability_of_getting_card = get_card_probability(c, cards_left);
         cards_left[c - 2]--;
         dealer_hand.AddCard(c);
         calculate_dealer_probabilities(dealer_hand, current_prob * probability_of_getting_card, results, cards_left);
         cards_left[c - 2]++;
         dealer_hand.RemoveLastCard();
      }
   }
}

// Returns the expected value of standing with the @player_hand.
double standing_expected_value(blackjack::Hand player_hand, std::array<double, 6> dealer_probabilities)
{
   // EV -> expected value, 
   // P(w) -> prob of player winning, P(l) -> prob of player lossing,
   // P(b) -> prob of dealer busting
   // P(n) -> prob of dealer having a total of n.
   //EV = 1*P(w) - 1*P(l) 
   int player_value = player_hand.Value();
   if(player_value>21) //player busted
      return -1;  //since P(w) = 0 & P(l) = 1 -> EV = 0-1 = -1

   // Since the dealer has to hit until they get atleast 17
   // the only chance to win if the value of the player count is less than 17
   // is that the dealer busts.
   // -> P(w) = P(b)
   // -> EV = P(w) - P(l) = P(b) - P(l)
   // -> P(l) = P(17)+P(18)+P(19)+P(20)+P(21)
   // -> EV = P(b) -P(17)-P(18)-P(19)-P(20)-P(21)
   // since P(b)+P(17)+P(18)+P(19)+P(20)+P(21) = 1
   // -> -P(17)-P(18)-P(19)-P(20)-P(21) = P(b) - 1
   // -> EV = P(b) + P(b) - 1 = 2P(b) - 1
   if(player_value<17)
      return 2*dealer_probabilities[5] -1;

   // prob_of_winning its initialized to the probability that the dealer busts.
   double prob_of_lossing = 0, prob_of_winning = dealer_probabilities[5];

   // Add to the probability of lossing all the probabilities that the dealer has a higher value than player.
   for(int i = player_value+1; i<=21; i++)
      prob_of_lossing += dealer_probabilities[i-17]; 
   
   // Add to the probability of winning all the probabilities that the dealer has a lesser value than player.
   for(int i = 17; i<player_value; i++)
      prob_of_winning += dealer_probabilities[i-17]; 
   
   return prob_of_winning - prob_of_lossing;
}

// Returns the expected value if the players doubles with @player_hand.
double doubling_expected_value(
   blackjack::Hand player_hand,
   std::array<double, 6> dealer_probabilities,
   std::array<int, 10> cards_left)
{
   double value = 0;
   for (int c = 2; c <= 11; c++)
   {
      if(cards_left[c-2] == 0)
         continue;
      player_hand.AddCard(c);
      value += get_card_probability(c, cards_left)*standing_expected_value(player_hand, dealer_probabilities);
      player_hand.RemoveLastCard();
   }
   return 2 * value;
}

// Returns the expected value if the players hits with @player_hand.
double hitting_expected_value(
   blackjack::Hand player_hand,
   std::array<double, 6> dealer_probabilities,
   std::array<int, 10> cards_left)
{
    double value = 0.0;

    if(player_hand.Value() >= 21)
        return -1.0;

    for (int c = 2; c <= 11; c++)
    {
      if(cards_left[c-2] == 0)
         continue;
      cards_left[c-2]--;
      player_hand.AddCard(c);
      double stand_value = standing_expected_value(player_hand, dealer_probabilities);
      double hit_again_value = hitting_expected_value(player_hand, dealer_probabilities, cards_left);
      player_hand.RemoveLastCard();
      cards_left[c-2]++;
      value += get_card_probability(c, cards_left) * std::max(stand_value, hit_again_value);
   }

   return value;
}


std::vector<std::pair<PlayerAction, double>> get_actions_ev(blackjack::Hand,std::array<double, 6>,std::array<int, 10>,blackjack::PlayOptions);

// Returns the expected value if the players splits with @player_hand.
double splitting_expected_value(
   blackjack::Hand player_hand,
   std::array<double, 6> dealer_probabilities,
   std::array<int, 10> cards_left,
   blackjack::PlayOptions options)
{
   double value = 0.0;
   auto hands = player_hand.Split();
   for(auto hand : {hands.first, hands.second})
   {
      for (int c = 2; c <= 11; c++)
      {
         if(cards_left[c-2] == 0)
            continue;
         cards_left[c-2]--;
         hand.AddCard(c);
         auto evs = get_actions_ev(
            hand,
            dealer_probabilities,
            cards_left,
            {
               (options.current_splits + 1) < options.max_splits, //can_split
               options.can_DAS,           //can_double
               false,                     //can_surrender
               options.can_DAS,           //can_DAS
               options.max_splits,
               options.current_splits + 1
            }
         );
         hand.RemoveLastCard();
         cards_left[c-2]++;
         auto [action, val] = get_max_value_action(evs);
         value += get_card_probability(c, cards_left) * val;
      }
   }
}

// Returns a vector of pairs of all the posible actions with their respective expected values.
std::vector<std::pair<PlayerAction, double>> get_actions_ev(
   blackjack::Hand player_hand,
   std::array<double, 6> dealer_probabilities,
   std::array<int, 10> cards_left,
   blackjack::PlayOptions options)
{
   std::vector<std::pair<PlayerAction, double>> res;

   if(options.can_surrender)
   {
      res.push_back({
         PlayerAction::SURRENDER,
         -0.5
      });
   }

   res.push_back({
      PlayerAction::STAND,
      standing_expected_value(player_hand, dealer_probabilities)
   });

   res.push_back({
      PlayerAction::HIT,
      hitting_expected_value(player_hand, dealer_probabilities, cards_left)
   });

   if(options.can_double)
   {
      res.push_back({
         PlayerAction::DOUBLE,
         doubling_expected_value(player_hand, dealer_probabilities, cards_left)
      });
   }

   if(player_hand.CanSplit() && options.can_split && options.current_splits < options.max_splits)
   {
      res.push_back({
         PlayerAction::SPLIT,
         splitting_expected_value(player_hand, dealer_probabilities, cards_left, options)
      });
   }
   return res;
}

}


PerfectStrategy::PerfectStrategy(int decks)
{
   this->on_shuffle(decks);
}

int PerfectStrategy::bet(int min, int max)
{
   return min;
}

PlayerAction PerfectStrategy::play(Hand player_hand, Card dealer_card, PlayOptions options)
{
   std::array<double, 6> dealer_probabilities = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
   calculate_dealer_probabilities(dealer_card, 1.0, dealer_probabilities, cards_left);
   auto evs = get_actions_ev(player_hand,dealer_probabilities,cards_left,options);
   auto [max_value_action, max_value] = get_max_value_action(evs);
   return max_value_action;
}

bool PerfectStrategy::wants_insurance()
{
   return false;
}

void PerfectStrategy::see_card(Card card) {
   cards_left[card-2]--;
}

void PerfectStrategy::see_cards(std::vector<Card> cards) {
   for(const auto& c : cards)
         cards_left[c-2]--;
}

void PerfectStrategy::on_shuffle(int decks)
 {
   for(int i = 0; i<10;i++){
      cards_left[i] = 4*decks;
   }
   cards_left[8] = 20*decks;
 }

}