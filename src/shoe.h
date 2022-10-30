#ifndef SHOE_H
#define SHOE_H

#include "card.h"
#include <vector>



class Shoe {
public:
   Shoe();
   Shoe(int deck_count);
   Card draw_card();             // removes a cards from the shoe and returns it
   void shuffle();               // resets the shoe to the starting ammount of cards, and shuffles them.
   double current_penetration();  //returns the ammount of cards used divided by the ammount of starting cards.
private:
   int deck_count;  // ammount of decks at the start.
   std::vector<Card> cards;
};

#endif