#include "round.h"

namespace bj {

SurrenderRound::SurrenderRound(){};

int SurrenderRound::decide_round(int dealer_count)
{
   return -0.5;
}

BJRound::BJRound(bool bj3_2)
{
   pays_3_to_2 = bj3_2;
}

int BJRound::decide_round(int dealer_count)
{
   return pays_3_to_2 ? 1.5 : (6 / 5.0);
}

DoubleRound::DoubleRound(int player_count)
{
   this->player_count = player_count;
}

int DoubleRound::decide_round(int dealer_count)
{
   if(dealer_count>21)
      return 2;
      
   if (player_count == dealer_count)
      return 0;
   
   return 2*(player_count > dealer_count ? 1 : -1);
}

SplitRound::SplitRound(Round *a, Round *b){
   this->a = a;
   this->b = b;
}

int SplitRound::decide_round(int dealer_count){
   return a->decide_round(dealer_count) + b->decide_round(dealer_count);
}


BustRound::BustRound(){};

int BustRound::decide_round(int dealer_count)
{
   return -1;
}

ToBeDecidedRound::ToBeDecidedRound(int player_count)
{
   this->player_count = player_count;
}

int ToBeDecidedRound::decide_round(int dealer_count)
{
   if(dealer_count>21)
      return 1;

   if (player_count == dealer_count) {
      return 0;
   }
   return player_count>dealer_count ? 1 : -1;
}

}