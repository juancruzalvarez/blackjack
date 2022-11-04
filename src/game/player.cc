#include "player.h"

namespace bj {

Player::Player(int starting_chips, Strategy *strategy, BettingStrategy *betting_strategy)
{
    this->starting_chips = starting_chips;
    this->current_chips = starting_chips;
    this->strategy = strategy;
    this->betting_strategy = betting_strategy;
}

PlayerAction Player::Play(Hand player_hand, Card dealer_card, PlayOptions options)
{
    return strategy->play(player_hand, dealer_card, options);
} 

int Player::Bet(int min_bet, int max_bet)
{
    return betting_strategy->bet(min_bet, max_bet);
}

bool Player::WantsInsurance()
{
    return betting_strategy->wants_insurance();
}

void Player::OnShuffle(int deck_count) 
{
    betting_strategy->on_shuffle(deck_count);
    strategy->on_shuffle(deck_count);
}

void Player::SeeCard(Card c) 
{
    betting_strategy->see_card(c);
    strategy->see_card(c);
}

void Player::SeeCards(std::vector<Card> cards) 
{
    betting_strategy->see_cards(cards);
    strategy->see_cards(cards);
}

int Player::CurrentChips()
{
    return this->current_chips;
}

int Player::StartingChips()
{
    return this->starting_chips;
}

void Player::AddChips(int chips)
{
    this->current_chips += chips;
}



}