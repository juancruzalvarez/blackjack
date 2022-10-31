#include <iostream>

#include "game/game.h"
#include "strategy/basic_strategy.h"
#include "strategy/improved_basic_strategy.h"
#include "strategy/chart.h"

int main() {

   blackjack::Chart chart;
   chart.Init("test_chart.bjc");
    /*srand(time(0)) ;
   blackjack::Player* worse = new blackjack::Player{5000,5000,new blackjack::BasicStrategy{}};
   blackjack::Player* bad = new blackjack::Player{5000,5000,new blackjack::ImprovedBasicStrategy{}};

   blackjack::Game game{blackjack::kStandardRules2Deck, {bad, worse}};
   for (int i = 0; i<5000; i++) {
      game.DoRound();

   }
   std::cout<<"bad player chips:"<<bad->current_chips<<"\n";
   std::cout<<"worse player chips:"<<worse->current_chips<<"\n";*/


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