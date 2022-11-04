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
   bj::Player *perfect = new bj::Player{
      50000,
      new bj::PerfectStrategy{2},
      new bj::MinBettingStrategy{}
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

   bj::Game game{bj::kStandardRules2Deck, {hi_lo, hi_op_ii, basic}};
   for (int i = 0; i<1000000; i++) {
     game.DoRound();
   }

   std::cout<<"p chips:"<<perfect->CurrentChips()<<"\n";
   std::cout<<"basic chips:"<<basic->CurrentChips()<<"\n";
   std::cout<<"hi_lo chips:"<<hi_lo->CurrentChips()<<"\n";
   std::cout<<"hi_op_ii chips:"<<hi_op_ii->CurrentChips()<<"\n";
   std::cout<<"bEV: "<<(basic->CurrentChips()-basic->StartingChips())/1000000.0;
   std::cout<<"hlEV: "<<(hi_lo->CurrentChips()-hi_lo->StartingChips())/1000000.0;
   std::cout<<"hoiiEV: "<<(hi_op_ii->CurrentChips()-hi_op_ii->StartingChips())/1000000.0;

   return 0;
}