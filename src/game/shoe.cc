#include "shoe.h"

#include <iostream>
namespace bj {

Shoe::Shoe()
{
   this->deck_count = 0;
}

Shoe::Shoe(int deck_count)
{
   this->deck_count = deck_count;
   Shuffle();
}

void Shoe::Shuffle()
{
   std::vector<Card> new_shoe;
   // Add deck_count ammount of full decks to the shoe.
   for (int i = 0; i < deck_count; i++)
   {
      new_shoe.insert(new_shoe.end(), &kFullDeck[0], &kFullDeck[52]);
   }

   // Shuffle the shoe, by randomly changing the position of the cards.
   for (int i = 0; i < new_shoe.size(); i++)
   {
      int r = i + (rand() % (new_shoe.size() - i));
      std::swap(new_shoe[i], new_shoe[r]);
   }

   cards = new_shoe;
}

Card Shoe::DrawCard()
{
   Card ret = cards.back();
   cards.pop_back();
   return ret;
}

double Shoe::GetShoePenetration()
{
   return 1 - cards.size() / double(deck_count * kCardsPerDeck);
}

}