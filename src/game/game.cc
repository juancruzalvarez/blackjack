#include <random>
#include <iostream>

#include "game.h"
#include "card.h"
#include "round.h"
#include "hand.h"

namespace blackjack {


Game::Game(Rules rules, std::vector<Player *> players)
{
   this->shoe = Shoe(rules.decks);
   this->rounds_played = 0;
   this->players = players;
   this->house_profit = 0;
   this->rules = rules;
}

// Round stages:
// All players place their bets.
// The dealer draws two cards, one the players can see and the other face down.
// If the dealer up card is an ace or a 10 valued card, he checks if he has blackjack.
// Each player plays its round
// Dealer plays its hand
// Dealer pays or collects depending on the result of each player round.

void Game::DoRound()
{
   int bets[kMaxPlayersPerTable];
   Hand hands[kMaxPlayersPerTable];
   Round *rounds[kMaxPlayersPerTable];
   for (int i = 0; i < players.size(); i++)
   {
      bets[i] = players[i]->strategy->bet(rules.min_bet, rules.max_bet);
   }
   Card dealer_up = DrawCard();
   Card dealer_down = shoe.DrawCard(); // We dont use game DrawCard here becouse the players do not see this card until the end of the round.
   Hand dealer_hand = Hand{dealer_up, dealer_down};
   // All player cards gets drawed before the first player gets to play.
   // This is not done in the order that is done in a traditional casino but its irrelevant to the result of the game.
   for (int i = 0; i < players.size(); i++)
   {
      hands[i] = Hand{DrawCard(), DrawCard()};
   }

   // Check for dealer bj.
   if (dealer_up == ACE || dealer_up == TEN)
   {
      if (rules.allows_insurance && dealer_up == ACE) // Offer insurance if up card is an ace and if rules allow it.
      {
         for (int i = 0; i < players.size(); i++)
         {
            // Insurance bet is half of the players bet, and it pays 2:1
            if (players[i]->strategy->wants_insurance())
            {
               if (dealer_hand.IsBlackJack())
               {
                  // Dealer has blackjack so the player wins insurance bet.
                  // Since its half the current player bet and pays 2:1, the player gets paid back their full bet.
                  players[i]->current_chips += bets[i];
                  house_profit -= bets[i];
               }
               else
               {
                  // Dealer doesent have blackjack, so the player losses the insurance bet, wich is half of their original bet.
                  players[i]->current_chips -= bets[i] * 0.5;
                  house_profit += bets[i] * 0.5;
               }
            }
         }
      }

      if (dealer_hand.IsBlackJack())
      {
         // If dealer has blackjack, take all the bets of the players that dont have blackjack.
         for (int i = 0; i < players.size(); i++)
         {
            if (hands[i].IsBlackJack())
            {
               players[i]->current_chips += bets[i];
            }
            else
            {
               house_profit += bets[i];
            }
         }

         // Show all players the dealers down card.
         for (const auto &p : players)
            p->strategy->see_card(dealer_down);

         // After this the round is over.
         return;
      }
   }

   // Play all the players rounds
   for (int i = 0; i < players.size(); i++)
   {
      rounds[i] = DoPlayerRound(
         players[i],
         hands[i],
         bets[i],
         dealer_up,
         {
            true, 
            true,
            rules.can_surrender,
            rules.can_DAS,
            rules.max_splits,
            0,
         });
   }

   // Play the dealers round.
   int dealer_value = DoDealerRound(dealer_hand);

   // Dealer collects or pays depending on the round result.
   for (int i = 0; i < players.size(); i++)
   {
      int round_result = rounds[i]->decide_round(dealer_value);
      // decide_round returns the value of the round for the player.
      house_profit -= round_result;
      players[i]->current_chips += round_result;
   }

   if ( shoe.GetShoePenetration() > rules.penetration_before_shuffle) {
      shoe.Shuffle();
      for(const auto& p : players)
         p->strategy->on_shuffle(rules.decks);
   }
}

// Player hand round stages:
// If the player has bj they automatically win their round.
// In the first turn they can split if they have pair, they can double, they can surrender, or they can do a normal thing.
// If the player surrenders(only if its allowed by the rules), they lose automatically half of their bet.
// If the player double, they double their bet, one more card is dealt and the round is decided against the dealer.
// If the player splits, they play each hand independently,
// else the player hits until they bust(go over 21) or they stand.
// If they bust, the hand is lost automatically
// If they stand the hand is decided against the dealer.
Round *Game::DoPlayerRound(Player *player, Hand player_hand, int bet, Card dealer_up, PlayOptions options)
{

   if (player_hand.IsBlackJack())
      return new BJRound{bet, rules.bj_3_to_2};

   PlayerAction action = player->strategy->play(player_hand, dealer_up, options);
   
   switch (action)
   {
   case PlayerAction::SURRENDER:
      return new SurrenderRound{bet};

   case PlayerAction::DOUBLE:
   {
      player_hand.AddCard(DrawCard());
      return new DoubleRound{bet, player_hand.Value()};
   }
   case PlayerAction::SPLIT:
   {
      std::pair<Hand, Hand> splited_hand = player_hand.Split();
      splited_hand.first.AddCard(DrawCard());
      splited_hand.second.AddCard(DrawCard());
      options.current_splits++;
      options.can_double = options.can_DAS;
      options.can_surrender = false;
      options.can_split = options.current_splits < options.max_splits;

      Round *first_round = DoPlayerRound(player,
                                        splited_hand.first,
                                        bet,
                                        dealer_up,
                                        options);

      Round *second_round = DoPlayerRound(player,
                                         splited_hand.second,
                                         bet,
                                         dealer_up,
                                         options);

      return new SplitRound{bet, first_round, second_round};
   }
   
   case PlayerAction::STAND:
      return new ToBeDecidedRound{bet, player_hand.Value()};

   case PlayerAction::HIT:
   {
      do
      {
         player_hand.AddCard(DrawCard());
         if (player_hand.Bust())
         {
            return new BustRound{bet};
         }
         // After hitting the player cant split, double or surrender.
         action = player->strategy->play(player_hand, dealer_up, {false, false, false, rules.can_DAS, options.max_splits, options.current_splits});
      } while (action == PlayerAction::HIT);

      return new ToBeDecidedRound{bet, player_hand.Value()};
   }
   }
}

// The dealer plays the same way each round.
// He cant split, double or surrender,
// and he must hit until his hand's value is atleast 17.
// Depending on the rules he might or might not hit a soft 17.
int Game::DoDealerRound(Hand dealer_hand)
{
   while (dealer_hand.Value() < 17 || (dealer_hand.Value() == 17 && dealer_hand.IsSoft() && rules.dealer_hit_s17))
      dealer_hand.AddCard(DrawCard());

   return dealer_hand.Value();
}

// draws a card from the shoe and shows it to all players.
Card Game::DrawCard()
{
   Card c = shoe.DrawCard();
   for (const auto &p : players)
   {
      p->strategy->see_card(c);
   }
   return c;
}

}