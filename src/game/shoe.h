#ifndef SHOE_H
#define SHOE_H

#include "card.h"
#include <vector>

namespace blackjack {

class Shoe {

public:
   Shoe();
   Shoe(int deck_count);
   Card DrawCard();             // Removes a card from the shoe and returns it.
   void Shuffle();               // Resets the shoe to the starting ammount of cards, and shuffles them.
   double GetShoePenetration(); // Returns the ammount of cards used divided by the ammount of starting cards.
private:
   int deck_count;               // Ammount of decks at the start.
   std::vector<Card> cards;

};

}

#endif