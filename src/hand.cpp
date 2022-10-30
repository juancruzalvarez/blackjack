#include "hand.h"

Hand::Hand(){}

Hand::Hand(Card first)
{
   this->cards.push_back(first);
}


Hand::Hand(Card first, Card second)
{
   this->cards.push_back(first);
   this->cards.push_back(second);
}

Hand::Hand(std::vector<Card> cards)
{
   this->cards.insert(this->cards.end(), cards.begin(), cards.end());
}

void Hand::AddCard(Card card) {
   cards.push_back(card);
}

int Hand::Value()
{
   int value = 0;
   int ace_count = 0;
   for (const auto &card : cards)
   {
      value += card;
      if (card == 11)
         ace_count++;
   }
   while (value > 21 && ace_count > 0)
   {
      ace_count--;
      value -= 10;
   }
   return value;
}

bool Hand::CanSplit()
{
   return (cards.size() == 2) && (cards[0] == cards[1]);
}

bool Hand::IsBlackJack()
{
   return (cards.size() == 2) && ((cards[0] + cards[1]) == 21);
}

std::pair<Hand, Hand> Hand::Split()
{
   return {Hand{cards.front()}, Hand{cards.back()}};
}

bool Hand::Bust(){
   return Value() > 21;
}
bool Hand::IsSoft(){
   for(const auto& card : cards){
      if (card == ACE)
         return true;
   }
   return false;
}