#include <iostream>

#include "game/game.h"
#include "strategy/basic_strategy.h"
#include "strategy/improved_basic_strategy.h"
#include "strategy/chart.h"
#include "strategy/chart_strategy.h"

std::string action_to_str(blackjack::ChartAction a)
{
   switch (a)
   {
   case blackjack::ChartAction::HIT:
      return "HIT";
   case blackjack::ChartAction::STAND:
      return "STAND";
   case blackjack::ChartAction::DOUBLE_OR_HIT:
      return "DOUBLE/HIT";
   case blackjack::ChartAction::DOUBLE_OR_STAND:
      return "DOUBLE/STAND";
   default:
      return "INVALID";
   }
}

std::string action_to_str(blackjack::PairChartAction a)
{
   switch (a)
   {
   case blackjack::PairChartAction::SPLIT:
      return "SPLIT";
   case blackjack::PairChartAction::DONT_SPLIT:
      return "DONT SPLIT";
   case blackjack::PairChartAction::SPLIT_IF_DAS:
      return "SPLIT IF DAS";
   default:
      return "INVALID";
   }
}


int main()
{

   blackjack::Chart chart;
   chart.Init("test_chart.bjc");
   blackjack::Player* basic_strategy_player = new blackjack::Player{5000,5000, new blackjack::ChartStrategy{chart}}; 
   blackjack::Player* bad = new blackjack::Player{5000,5000,new blackjack::ImprovedBasicStrategy{}};

   srand(time(0)) ;

  blackjack::Game game{blackjack::kStandardRules2Deck, {basic_strategy_player, bad}};
  for (int i = 0; i<5000; i++) {
     game.DoRound();

  }
  std::cout<<"basic_strategy player chips:"<<basic_strategy_player->current_chips<<"\n";
  std::cout<<"bad player chips:"<<bad->current_chips<<"\n";

   /*std::cout<<"Hand test: \n"; 6343 - 6878
   int go_again =    1;
   while(go_again) {
      std::cout<<"Enter cards:(0 to end)\n";
      blackjack::Card card = 1;
      blackjack::Hand hand{};
      for(;;){
         std::cin>>card;
         if (card == 0)
         break;
         hand.AddCard(card);
      }
      std::cout<<"Hand:\n";
      std::cout<<"Value:"<<hand.Value()<<"\n";
      std::cout<<"Bust:"<<hand.Bust()<<"\n";
      std::cout<<"Bj:"<<hand.IsBlackJack()<<"\n";
      std::cout<<"CanSplit:"<<hand.CanSplit()<<"\n";
      std::cout<<"IsSoft:"<<hand.IsSoft()<<"\n";
      std::cout<<"Enter 1 to go again.\n";1
      std::cin>>go_again;
   }*/

   return 0;
}