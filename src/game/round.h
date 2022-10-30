#ifndef ROUND_H
#define ROUND_H


namespace blackjack {

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
   virtual int decide_round(int dealer_count) = 0;

protected:
   int starting_bet;
};

class SurrenderRound : public Round
{
public:
   SurrenderRound(int bet);
   int decide_round(int dealer_count);
};

class BJRound : public Round
{
public:
   BJRound(int bet, bool bj3_2);
   int decide_round(int dealer_count);

private:
   bool pays_3_to_2;
};

class DoubleRound : public Round
{
public:
   DoubleRound(int bet, int player_count);
   int decide_round(int dealer_count);

private:
   int player_count;
};

class SplitRound : public Round
{
public:
   SplitRound(int bet, Round *a, Round *b);
   int decide_round(int dealer_count);

private:
   Round *a, *b;
};

class BustRound : public Round
{
public:
   BustRound(int bet);
   int decide_round(int dealer_count);
};

class ToBeDecidedRound : public Round
{
public:
   ToBeDecidedRound(int bet, int player_count);
   int decide_round(int dealer_count);
private:
   int player_count;
};

}

#endif
