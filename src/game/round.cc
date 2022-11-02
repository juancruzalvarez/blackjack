#include "round.h"

namespace blackjack {

SurrenderRound::SurrenderRound(int bet)
{
   starting_bet = bet;
};

int SurrenderRound::decide_round(int dealer_count)
{
   return -starting_bet*0.5;
}

BJRound::BJRound(int bet, bool bj3_2)
{
   starting_bet = bet;
   pays_3_to_2 = bj3_2;
}

int BJRound::decide_round(int dealer_count)
{
   return pays_3_to_2 ? starting_bet * 1.5 : starting_bet * (6 / 5.0);
}

DoubleRound::DoubleRound(int bet, int player_count)
{
   starting_bet = bet;
   this->player_count = player_count;
}

int DoubleRound::decide_round(int dealer_count)
{
   if(dealer_count>21)
      return starting_bet;
      
   if (player_count == dealer_count) {
      return 0;
   }
   return starting_bet*2*(player_count > dealer_count ? 1 : -1);
}

  SplitRound::SplitRound(int bet, Round *a, Round *b){
   starting_bet = bet;
   this->a = a;
   this->b = b;
  }
   int SplitRound::decide_round(int dealer_count){
      return a->decide_round(dealer_count) + b->decide_round(dealer_count);
   }


BustRound::BustRound(int bet)
{
   starting_bet = bet;
};

int BustRound::decide_round(int dealer_count)
{
   return -starting_bet;
}

ToBeDecidedRound::ToBeDecidedRound(int bet, int player_count)
{
   starting_bet = bet;
   this->player_count = player_count;
}

int ToBeDecidedRound::decide_round(int dealer_count)
{
   if(dealer_count>21)
      return starting_bet;

   if (player_count == dealer_count) {
      return 0;
   }
   return starting_bet * ( player_count>dealer_count ? 1 : -1);
}

}