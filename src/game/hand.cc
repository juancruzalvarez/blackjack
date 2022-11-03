#include "hand.h"

namespace bj {

Hand::Hand() {}

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

void Hand::AddCard(Card card)
{
   cards.push_back(card);
}

int Hand::RawValue()
{
   int value = 0;
   for (const auto &card : cards)
      value += card;
   return value;
}

int Hand::Value()
{
   int value = 0;
   int ace_count = 0;
   // First treat all aces as 11.
   for (const auto &card : cards)
   {
      value += card;
      if (card == 11)
         ace_count++;
   }
   // If the value of the hand excedes 21, and there are aces, treat them as 1.
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

bool Hand::Bust()
{
   return Value() > 21;
}

bool Hand::IsSoft()
{
   int value = 0;
   int ace_count = 0;
   // First treat all aces as 11.
   for (const auto &card : cards)
   {
      value += card;
      if (card == 11)
         ace_count++;
   }
   // If the value of the hand excedes 21, and there are aces, treat them as 1.
   while (value > 21 && ace_count > 0)
   {
      ace_count--;
      value -= 10;
   }
   //ace_count now has the number of aces that can be treated as a 1 or as an 11 without busting.
   return ace_count>0;
}

void Hand::RemoveLastCard() {
   cards.pop_back();
}

}