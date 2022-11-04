#include <iostream>

#include "game/game.h"
#include "strategy/basic_strategy.h"
#include "strategy/improved_basic_strategy.h"
#include "strategy/perfect_strategy.h"
#include "strategy/chart.h"
#include "strategy/chart_strategy.h"
#include "strategy/count_betting_strategy.h"
#include "strategy/min_betting_strategy.h"

std::string action_to_str(bj::ChartAction a)
{
   switch (a)
   {
   case bj::ChartAction::HIT:
      return "HIT";
   case bj::ChartAction::STAND:
      return "STAND";
   case bj::ChartAction::DOUBLE_OR_HIT:
      return "DOUBLE/HIT";
   case bj::ChartAction::DOUBLE_OR_STAND:
      return "DOUBLE/STAND";
   default:
      return "INVALID";
   }
}

std::string action_to_str(bj::PairChartAction a)
{
   switch (a)
   {
   case bj::PairChartAction::SPLIT:
      return "SPLIT";
   case bj::PairChartAction::DONT_SPLIT:
      return "DONT SPLIT";
   case bj::PairChartAction::SPLIT_IF_DAS:
      return "SPLIT IF DAS";
   default:
      return "INVALID";
   }
}


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

   bj::Game game{bj::kStandardRules2Deck, {perfect}};
   for (int i = 0; i<10000; i++) {
     game.DoRound();

   }
     std::cout<<"p chips:"<<perfect->CurrentChips()<<"\n";

   std::cout<<"basic chips:"<<basic->CurrentChips()<<"\n";
  std::cout<<"hi_lo chips:"<<hi_lo->CurrentChips()<<"\n";
  std::cout<<"hi_op_ii chips:"<<hi_op_ii->CurrentChips()<<"\n";

   /*std::cout<<"Hand test: \n"; 6343 - 6878
   int go_again =    1;
   while(go_again) {
      std::cout<<"Enter cards:(0 to end)\n";
      bj::Card card = 1;
      bj::Hand hand{};
      for(;;){
         std::cin>>card;
         if (card == 0)
         break;
         hand.AddCard(card);
      }
      std::cout<<"Hand:\n";
      std::cout<<"Value:"<<hand.Value()<<"\n";
      std::cout<<"Bust:"<<hand.Bust()<<"\n";
      std::cout<<"Bj:"<<hand.Isbj()<<"\n";
      std::cout<<"CanSplit:"<<hand.CanSplit()<<"\n";
      std::cout<<"IsSoft:"<<hand.IsSoft()<<"\n";
      std::cout<<"Enter 1 to go again.\n";1
      std::cin>>go_again;
   }*/

   return 0;
}