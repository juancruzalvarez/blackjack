#include "round.h"

namespace bj {

SurrenderRound::SurrenderRound(){};

double SurrenderRound::decide_round(int dealer_count)
{
   return -0.5;
}
std::string SurrenderRound::ToString(){ return "Surrender"; }

BJRound::BJRound(bool bj3_2)
{
   pays_3_to_2 = bj3_2;
}

double BJRound::decide_round(int dealer_count)
{
   return pays_3_to_2 ? 1.5 : (6 / 5.0);
}

std::string BJRound::ToString(){ return "BJ"; }

DoubleRound::DoubleRound(int player_count)
{
   this->player_count = player_count;
}

double DoubleRound::decide_round(int dealer_count)
{
   if(dealer_count>21)
      return 2;
      
   if (player_count == dealer_count)
      return 0;
   
   return 2*(player_count > dealer_count ? 1 : -1);
}

std::string DoubleRound::ToString() { return "Double P: "+std::to_string(player_count); }

SplitRound::SplitRound(Round *a, Round *b){
   this->a = a;
   this->b = b;
}

double SplitRound::decide_round(int dealer_count){
   return a->decide_round(dealer_count) + b->decide_round(dealer_count);
}

std::string SplitRound::ToString(){
   return "Split:\n A:" + a->ToString() + "\nB:" + b->ToString();
}

BustRound::BustRound(){};

double BustRound::decide_round(int dealer_count)
{
   return -1;
}


std::string BustRound::ToString(){
   return "Bust";
}


ToBeDecidedRound::ToBeDecidedRound(int player_count)
{
   this->player_count = player_count;
}

double ToBeDecidedRound::decide_round(int dealer_count)
{
   if(dealer_count>21)
      return 1;

   if (player_count == dealer_count) {
      return 0;
   }
   return player_count>dealer_count ? 1 : -1;
}

std::string ToBeDecidedRound::ToString(){
   return "TBD: " + std::to_string(player_count);
}

}