#include <iostream>

#include "game/game.h"
#include "strategy/basic_strategy.h"

int main() {
    srand(time(0)) ;
   /*blackjack::Player* p = new blackjack::Player{5000,5000,new blackjack::BasicStrategy{}};
   blackjack::Game game{blackjack::kStandardRules2Deck, {p}};
   for (int i = 0; i<5; i++) {
      game.DoRound();
      std::cout<<"player chips:"<<p->current_chips<<"\n";
   }*/
   /*std::cout<<"Hand test: \n";
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