#include <iostream>

#include "game/game.h"
#include "strategy/basic_strategy.h"
#include "strategy/improved_basic_strategy.h"
#include "strategy/perfect_strategy.h"
#include "strategy/chart.h"
#include "strategy/chart_strategy.h"
#include "strategy/count_betting_strategy.h"
#include "strategy/min_betting_strategy.h"


int main()
{

   bj::Chart chart;
   chart.Init("test_chart.bjc");
   bj::Player *perfect_hi_lo = new bj::Player{
      50000,
      new bj::PerfectStrategy{2},
      new bj::CountBettingStrategy{bj::count::kHiLoValues, bj::count::basic_betting, 2}
   };

   bj::Player *perfect_hi_op_ii = new bj::Player{
      50000,
      new bj::PerfectStrategy{2},
      new bj::CountBettingStrategy{bj::count::kHiOpIIValues, bj::count::basic_betting, 2}
   };

   bj::Player *basic = new bj::Player{
      50000,
      new bj::ChartStrategy{chart},
      new bj::MinBettingStrategy{}
   };

   bj::Player *hi_lo = new bj::Player{
      50000,
      new bj::ChartStrategy{chart},
      new bj::CountBettingStrategy{bj::count::kHiLoValues, bj::count::basic_betting, 2}
   };

   bj::Player *hi_op_ii = new bj::Player{
      50000,
      new bj::ChartStrategy{chart},
      new bj::CountBettingStrategy{bj::count::kHiOpIIValues, bj::count::basic_betting, 2}
   };
   
   

   srand(time(0)) ;

   bj::Game game{bj::kStandardRules2Deck, {hi_lo}};
   for (int i = 0; i<50; i++) {
     game.DoRound();
   }

   std::cout<<"pho:"<<hi_lo->CurrentChips()<<"\n";
   //std::cout<<"hi_lo chips:"<<hi_lo->CurrentChips()<<"\n";
   //std::cout<<"hi_op_ii chips:"<<hi_op_ii->CurrentChips()<<"\n";
   std::cout<<"bhoEV: "<<(hi_lo->CurrentChips()-perfect_hi_op_ii->StartingChips())/1000.0;
  // std::cout<<"hlEV: "<<(hi_lo->CurrentChips()-hi_lo->StartingChips())/1000000.0;
  // std::cout<<"hoiiEV: "<<(hi_op_ii->CurrentChips()-hi_op_ii->StartingChips())/1000000.0;

   return 0;
}