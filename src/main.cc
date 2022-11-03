#include <iostream>

#include "game/game.h"
#include "strategy/basic_strategy.h"
#include "strategy/improved_basic_strategy.h"
#include "strategy/perfect_strategy.h"
#include "strategy/chart.h"
#include "strategy/chart_strategy.h"

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
   bj::Player* perfect_strategy_player = new bj::Player{10000,10000, new bj::PerfectStrategy{bj::kStandardRules2Deck.decks}};
   bj::Player* basic_strategy_player = new bj::Player{10000,10000, new bj::ChartStrategy{chart}}; 
   bj::Player* bad = new bj::Player{10000,10000,new bj::ImprovedBasicStrategy{}};

   srand(time(0)) ;

  bj::Game game{bj::kStandardRules2Deck, {perfect_strategy_player, basic_strategy_player, bad}};
  for (int i = 0; i<15000; i++) {
     game.DoRound();

  }
   std::cout<<"perfect_strategy player chips:"<<perfect_strategy_player->current_chips<<"\n";
  std::cout<<"basic_strategy player chips:"<<basic_strategy_player->current_chips<<"\n";
  std::cout<<"bad player chips:"<<bad->current_chips<<"\n";

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