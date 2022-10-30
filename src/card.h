#ifndef CARD_H
#define CARD_H

// In blackjack, the suit of the card is irelevant
// 11 represents ace, 10 represents all face cards(J, Q, K) and 10s, and the rest are represented by their number.
typedef int Card;

const int kCardsPerDeck = 52;

// full deck of 52 cards.
const Card kFullDeck[] = {
    11, 11, 11, 11,  // 4 aces
    2, 2, 2, 2,
    3, 3, 3, 3,
    4, 4, 4, 4,
    5, 5, 5, 5,
    6, 6, 6, 6,
    7, 7, 7, 7,
    8, 8, 8, 8,
    9, 9, 9, 9,
    10, 10, 10, 10,  // 4 tens
    10, 10, 10, 10,  // 4 jacks
    10, 10, 10, 10,  // 4 queens
    10, 10, 10, 10,  // 4 kings
};

enum Cards
{
   TWO = 2,
   THREE,
   FOUR,
   FIVE,
   SIX,
   SEVEN,
   NINE,
   TEN,
   ACE,
};

#endif