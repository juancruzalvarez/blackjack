#include <random>

#include "game.h"
#include "hand.h"

Card draw(std::vector<Card> &deck)
{
   Card c = deck.back();
   deck.pop_back();
   return c;
}

std::vector<Card> shuffle(int decks)
{
   std::vector<Card> deck;
   for (int i = 0; i < decks; i++)
   {
      deck.insert(deck.end(), &DECK[0], &DECK[51]);
   }

   for (int i = 0; i < deck.size(); i++)
   {
      int r = i + (rand() % (deck.size() - i));
      std::swap(deck[i], deck[r]);
   }
   return deck;
}

Game new_game(Rules rules, std::vector<Player *> players)
{
   Game game;
   game.cards = shuffle(rules.decks);
   game.hands_played = 0;
   game.players = players;
   game.profit = 0;
   game.rules = rules;
}

// hand stages:
// place bets
// deal all cards
// check dealer bj
// each player plays its round
// dealer plays its hand
// dealer pays or collects each hand

void do_hand(Game &game)
{
   Card dealer_up = draw(game.cards), dealer_down = draw(game.cards);
   std::vector<Card> player_cards;

   for (int i = 0; i < game.players.size() * 2; i++)
   {
      player_cards.push_back(draw(game.cards));
   }

   for (int i = 0; i < game.players.size(); i++)
   {
      game.players[i]->strat->see_card(dealer_up);
      game.players[i]->strat->see_card(dealer_down);
      game.players[i]->strat->see_cards(player_cards);

      Card p_1 = player_cards[2 * i], p_2 = player_cards[2 * i + 1];
      int ace_count = (p_1 == 1) + (p_2 == 1);
      PlayerAction action = game.players[i]->strat->play(p_1 + p_2, ace_count, dealer_up, p_1 == p_2, true, game.rules.can_surrender);
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
Hand *player_hand(Game &game, Player *player, int bet, int current_count, int ace_count, Card dealer_up, bool can_split, bool can_double, bool can_surrender)
{
   Hand *ret;
   std::vector<Card> cards_seen;

   if (current_count == 21)
   {
      return new BJHand{bet, game.rules.bj_3_to_2};
   }

   PlayerAction action = player->strat->play(current_count, ace_count, dealer_up, true, true, true);
   switch (action)
   {
   case PlayerAction::SURRENDER:
      ret = new SurrenderHand{bet};
      break;
   case PlayerAction::DOUBLE:
      ret new DoubleHand{bet, current_count};
      break;
   case PlayerAction::SPLIT:
      Card first_hand_card = draw(game.cards), second_hand_card = draw(game.cards);
      cards_seen.push_back(first_hand_card);
      cards_seen.push_back(second_hand_card);
      Hand *first_hand = player_hand(game,
                                     player,
                                     bet,
                                     (current_count / 2) + first_hand_card,
                                     (ace_count / 2) + (first_hand_card == 1),
                                     dealer_up,
                                     true,
                                     game.rules.can_DAS,
                                     false);
      Hand *second_hand = player_hand(game,
                                      player,
                                      bet,
                                      (current_count / 2) + second_hand_card,
                                      (ace_count / 2) + (second_hand_card == 1),
                                      dealer_up,
                                      true,
                                      game.rules.can_DAS,
                                      false);
      ret = new SplitHand{bet, first_hand, second_hand};
      break;
   case PlayerAction::STAND:
      ret = new ToBeDecidedHand{bet, current_count};
      break;
   case PlayerAction::HIT:
      do {
         Card new_card = draw(game.cards);
         cards_seen.push_back(new_card);
         current_count += new_card;
         if (current_count > 21) {
            return new BustHand {bet};
         }
         action = player->strat->play(current_count, ace_count + (new_card == 1), dealer_up, false, false, false);
      }while(action == PlayerAction::HIT);
      ret = new ToBeDecidedHand{bet, current_count};
      break;
   }

   for(const auto& p : game.players){
      p->strat->see_cards(cards_seen);
   }
   
   return ret;
}
