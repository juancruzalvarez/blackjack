#ifndef RULES_H
#define RULES_H

namespace bj {

   struct Rules
   {
      int decks;                        // Amount of decks that are shufled together.
      bool dealer_hit_s17;              // Does the dealer hit or stands soft 17
      bool can_surrender;               // Is the player allowed to surrender their hand.
      bool can_DAS;                     // Can the player double after spliting.
      bool bj_3_to_2;                   // Blackjack pays 3:2 or 6:5.
      bool allows_insurance;            // If dealer's up card is an ace all players are offered to make insurance bet, pays 2:1
      bool can_hit_after_spliting_aces; // Can the player hit after spliting aces?
      int max_splits;                   // Max ammount of times a player can split a hand in a particular round.
      int min_bet, max_bet;             // Betting range.
      float penetration_before_shuffle; // What percentaje of the cards are used before the cards are shuffled again.  (0.0 : 1.0)
   };

   const Rules kStandardRules2Deck {
      2,       // Two decks.
      false,   // Dealers stands on all 17s.
      true,    // Player can surrender.
      true,    // Player can double after splitting.
      true,    // Blackjack pays 3:2.
      true,    // Players are offered insurance on dealer up card ace.
      false,   // Players cannot hit after splitting aces.
      1,       // Player is allowed to split their hand a maximum of 3 times.
      50, 1000,  // Betting rangue [5 : 100]
      0.7,     // 70% of the shoe is seen before it gets shuffled again.
   };

   const Rules kStandardRules6Deck {
      6,       // Six decks.
      false,   // Dealers stands on all 17s.
      true,    // Player can surrender.
      true,    // Player can double after splitting.
      true,    // Blackjack pays 3:2.
      true,    // Players are offered insurance on dealer up card ace.
      false,   // Players cannot hit after splitting aces.
      3,       // Player is allowed to split their hand a maximum of 3 times.
      50, 1000,  // Betting rangue [5 : 100]
      0.7,     // 70% of the shoe is seen before it gets shuffled again.
   };

}

#endif