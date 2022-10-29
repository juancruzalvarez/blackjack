#include "hand.h"

SurrenderHand::SurrenderHand(int bet)
{
   starting_bet = bet;
};

int SurrenderHand::decide_hand(int dealer_count)
{
   return -starting_bet*0.5;
}

BJHand::BJHand(int bet, bool bj3_2)
{
   starting_bet = bet;
   pays_3_to_2 = bj3_2;
}

// TODO: if dealer has bj?
int BJHand::decide_hand(int dealer_count)
{
   return pays_3_to_2 ? starting_bet * 1.5 : starting_bet * (6 / 5.0);
}

DoubleHand::DoubleHand(int bet, int player_count)
{
   starting_bet = bet;
   this->player_count = player_count;
}

//TODO: if tie??
int DoubleHand::decide_hand(int dealer_count)
{
   if (player_count == dealer_count) {
      return 0;
   }
   return starting_bet*2*(player_count>dealer_count ? 1 : -1);
}

  SplitHand::SplitHand(int bet, Hand *a, Hand *b){
   starting_bet = bet;
   this->a = a;
   this->b = b;
  }
   int SplitHand::decide_hand(int dealer_count){
      return a->decide_hand(dealer_count) + b->decide_hand(dealer_count);
   }


BustHand::BustHand(int bet)
{
   starting_bet = bet;
};

int BustHand::decide_hand(int dealer_count)
{
   return -starting_bet;
}

ToBeDecidedHand::ToBeDecidedHand(int bet, int player_count)
{
   starting_bet = bet;
   this->player_count = player_count;
}

int ToBeDecidedHand::decide_hand(int dealer_count)
{
   if (player_count == dealer_count) {
      return 0;
   }
   return starting_bet*(player_count>dealer_count ? 1 : -1);
}