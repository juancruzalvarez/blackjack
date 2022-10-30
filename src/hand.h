#ifndef HAND_H
#define HAND_H

#include <vector>

#include "card.h"

// Hand represents a set of cards.
class Hand
{

public:
   Hand();
   Hand(Card first);
   Hand(Card first, Card second);
   Hand(std::vector<Card> cards);
   void AddCard(Card card); 
   int Value();   // Returns the value of the hand. If the hands has an ace or more, it treats them as 11 unless that would make the hand bust.
   bool CanSplit();  // Returns true if the hand is two cards of the same value.
   bool IsBlackJack();  // Returns true if the hand is an ace and a ten-valued card.
   bool Bust();   // Returns true if the hand's value is over 21.
   bool IsSoft(); // Returns true if the hand has an ace.
   std::pair<Hand, Hand> Split(); //Returns a pair of hands, one with the first card of the hand, and another with the second. Asumes the hand has only two cards.
private:
   std::vector<Card> cards;
   
};

#endif