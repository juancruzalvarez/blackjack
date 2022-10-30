#ifndef HAND_H
#define HAND_H

#include <vector>

#include "card.h"

class Hand
{

public:
   Hand();
   Hand(Card first);
   Hand(Card first, Card second);
   Hand(std::vector<Card> cards);
   void AddCard(Card card);
   int Value();
   bool CanSplit();
   bool IsBlackJack();
   bool Bust();
   bool IsSoft();
   std::pair<Hand, Hand> Split();
private:
   std::vector<Card> cards;
   
};

#endif