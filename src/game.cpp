#include <random>

#include "game.h"
#include "card.h"
#include "round.h"
#include "hand.h"

Game::Game(Rules rules, std::vector<Player *> players)
{
   this->shoe = Shoe(rules.decks);
   this->rounds_played = 0;
   this->players = players;
   this->house_profit = 0;
   this->rules = rules;
}

// round stages:
// place bets
// deal all cards
// check dealer bj
// each player plays its round
// dealer plays its hand
// dealer pays or collects each hand

void Game::do_round()
{
   int bets[kMaxPlayersPerTable];
   Hand hands[kMaxPlayersPerTable];
   Round* rounds [kMaxPlayersPerTable];
   for (int i = 0; i < players.size(); i++)
   {
      bets[i] = players[i]->strat->bet(rules.min_bet, rules.max_bet);
   }
   Card dealer_up = draw_card();
   Card dealer_down = shoe.draw_card(); // we dont use game draw_card here becouse the players do not see this card until the end of the round.
   Hand dealer_hand = Hand {dealer_up, dealer_down};
   // all player cards gets drawed before the first player gets to play.
   // this is not done in the order that is done in a traditional casino but its irrelevant to the result of the game so it doesent matter.
   for (int i = 0; i < players.size(); i++)
   {
      hands[i] = Hand{draw_card(), draw_card()};
   }

   // check for dealer bj.
   if (dealer_up == 11 || dealer_up == 10)
   {
      if (rules.allows_insurance && dealer_up == 11) // offer insurance if up card is an ace and if rules allow it.
      {
         for (int i = 0; i < players.size(); i++)
         {
            if (players[i]->strat->wants_insurance())
            {
               if (dealer_hand.IsBlackJack())
               {
                  players[i]->current_chips += bets[i];
                  house_profit -= bets[i];
               }
               else
               {
                  players[i]->current_chips -= bets[i] * 0.5;
                  house_profit += bets[i] * 0.5;
               }
            }
         }
      }

      if (dealer_hand.IsBlackJack())
      {
         // if dealer has blackjack take all the bets of the players that dont have blackjack.
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
         for (const auto& p : players)
            p->strat->see_card(dealer_down);
         return;
      }
   }

   for (int i = 0; i < players.size(); i++)
   {
      rounds[i] = player_round(players[i], hands[i], bets[i], dealer_up, true, true, true, 0);
   }

   int dealer_value = dealer_round(dealer_hand);
   for (int i = 0; i < players.size(); i++)
   {
      int round_result = rounds[i]->decide_round(dealer_value);
      house_profit -= round_result;
      players[i]->current_chips += round_result;
   }
   
}

// player hand round stages:
// if the player has bj they automatically win their round.
// in the first turn they can split if they have pair, they can double, they can surrender, or they can do a normal thing.
// if the player surrenders(only if its allowed by the rules), they lose automatically half of their bet.
// if the player double, they double their bet, one more card is dealt and the round is decided against the dealer.
// if the player splits, they play each hand independently.
// else the player hits until they bust(go over 21) or they stand.
// if they bust the hand is lost automatically
// if they stand the hand is decided against the dealer.
Round *Game::player_round(Player *player, Hand player_hand, int bet, Card dealer_up, bool can_split, bool can_double, bool can_surrender, int splits_done)
{
   Round *ret;
   if (player_hand.IsBlackJack())
   {
      return new BJRound{bet, rules.bj_3_to_2};
   }

   PlayerAction action = player->strat->play(player_hand, dealer_up, true, true, true);
   std::pair<Hand,Hand> splited_hand;
   switch (action)
   {
      
   case PlayerAction::SURRENDER:
      return new SurrenderRound{bet};
   case PlayerAction::DOUBLE:
      player_hand.AddCard(draw_card());
      return new DoubleRound{bet, player_hand.Value()};
   case PlayerAction::SPLIT:
      splited_hand = player_hand.Split();
      splited_hand.first.AddCard(draw_card());
      splited_hand.second.AddCard(draw_card());
      Round *first_round = player_round(player,
                                        splited_hand.first,
                                        bet,
                                        dealer_up,
                                        splits_done < rules.max_splits,
                                        rules.can_DAS,
                                        false,
                                        splits_done + 1);
      Round *second_round = player_round(player,
                                         splited_hand.second,
                                         bet,
                                         dealer_up,
                                         splits_done < rules.max_splits,
                                         rules.can_DAS,
                                         false,
                                         splits_done + 1);
      return new SplitRound{bet, first_round, second_round};
   case PlayerAction::STAND:
      return new ToBeDecidedRound{bet, player_hand.Value()};
   case PlayerAction::HIT:
      do
      {
         player_hand.AddCard(draw_card());
         if (player_hand.Value() > 21)
         {
            return new BustRound{bet};
         }
         action = player->strat->play(player_hand, dealer_up, false, false, false);
      } while (action == PlayerAction::HIT);
      return new ToBeDecidedRound{bet, player_hand.Value()};
   }
}

int Game::dealer_round(Hand dealer_hand) {
   while(dealer_hand.Value() < 17)
      dealer_hand.AddCard(draw_card());
   
   if(dealer_hand.Value() == 17 && dealer_hand.IsSoft() && rules.dealer_hit_s17)
      dealer_hand.AddCard(draw_card());

   while(dealer_hand.Value() < 17)
      dealer_hand.AddCard(draw_card());

   return dealer_hand.Value();
}

Card Game::draw_card()
{
   Card c = shoe.draw_card();
   for (const auto &p : players)
   {
      p->strat->see_card(c);
   }
   return c;
}