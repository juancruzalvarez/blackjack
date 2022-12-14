#ifndef ROUND_H
#define ROUND_H

#include <string>

namespace bj {

enum class RoundResult
{
   BLACKJACK,      // player hits blackjack with their first two cards.
   SURRENDER,      // player surrenders their hand, automatically lossing half their bet.
   DOUBLE,         // player doubles their bet, the hands gets decided against the dealer.
   SPLIT,          // player splits their hand in two, both hands get decided independently of each other.
   BUST,           // player goes over 21, lossing their bet automatically.
   AGAINST_DEALER, // the player stands before busting, the hands gets decided against the dealer.
};

class Round
{
public:
   virtual double decide_round(int dealer_count) = 0;
   virtual std::string ToString() = 0;
};

class SurrenderRound : public Round
{
public:
   SurrenderRound();
   double decide_round(int dealer_count);
   std::string ToString();
};

class BJRound : public Round
{
public:
   BJRound(bool bj3_2);
   double decide_round(int dealer_count);
   std::string ToString();
private:
   bool pays_3_to_2;
};

class DoubleRound : public Round
{
public:
   DoubleRound(int player_count);
   double decide_round(int dealer_count);
   std::string ToString();
private:
   int player_count;
};

class SplitRound : public Round
{
public:
   SplitRound(Round *a, Round *b);
   double decide_round(int dealer_count);
   std::string ToString();
private:
   Round *a, *b;
};

class BustRound : public Round
{
public:
   BustRound();
   double decide_round(int dealer_count);
   std::string ToString();
};

class ToBeDecidedRound : public Round
{
public:
   ToBeDecidedRound(int player_count);
   double decide_round(int dealer_count);
   std::string ToString();
private:
   int player_count;
};

}

#endif
