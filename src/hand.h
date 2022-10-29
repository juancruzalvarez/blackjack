#ifndef HAND_H
#define HAND_H

#include "game.h"

enum class HandResult
{
   BLACKJACK,      // player hits blackjack with their first two cards.
   SURRENDER,      // player surrenders their hand, automatically lossing half their bet.
   DOUBLE,         // player doubles their bet, the hands gets decided against the dealer.
   SPLIT,          // player splits their hand in two, both hands get decided independently of each other.
   BUST,           // player goes over 21, lossing their bet automatically.
   AGAINST_DEALER, // the player stands before busting, the hands gets decided against the dealer.
};

class Hand
{
public:
   virtual int decide_hand(int dealer_count) = 0;

protected:
   int starting_bet;
};

class SurrenderHand : public Hand
{
public:
   SurrenderHand(int bet);
   int decide_hand(int dealer_count);
};

class BJHand : public Hand
{
public:
   BJHand(int bet, bool bj3_2);
   int decide_hand(int dealer_count);

private:
   bool pays_3_to_2;
};

class DoubleHand : public Hand
{
public:
   DoubleHand(int bet, int player_count);
   int decide_hand(int dealer_count);

private:
   int player_count;
};

class SplitHand : public Hand
{
public:
   SplitHand(int bet, Hand *a, Hand *b);
   int decide_hand(int dealer_count);

private:
   Hand *a, *b;
};

class BustHand : public Hand
{
public:
   BustHand(int bet);
   int decide_hand(int dealer_count);
};

class ToBeDecidedHand : public Hand
{
public:
   ToBeDecidedHand(int bet, int player_count);
   int decide_hand(int dealer_count);
private:
   int player_count;
};

#endif