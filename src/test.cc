#include <iostream>
#include <array>

#include "game/card.h"
#include "game/hand.h"

double get_card_probability(blackjack::Card c, std::array<int, 10> cards_left)
{
    double total_cards_left = 0;
    for (const auto &c : cards_left)
        total_cards_left += c;
    return cards_left[c - 2] / total_cards_left;
}

// time complexity O(n) = 10^n where n is the ammount of cards drawed before hitting at least 16 or busting.
void calculate_dealer_probabilities(blackjack::Hand dealer_hand, double current_prob,
                                    std::array<double, 5> &results, std::array<int, 10> cards_left)
{
    if (dealer_hand.Value() > 16)
    {
        std::cout << "cp:" << current_prob << "\n";
        results[std::min(dealer_hand.Value() - 17, 5)] += current_prob;
        return;
    }
    for (int c = 2; c <= 11; c++)
    {
        if (cards_left[c - 2] > 0)
        {
            double probability_of_getting_card = get_card_probability(c, cards_left);
            cards_left[c - 2]--;

            dealer_hand.AddCard(c);
            calculate_dealer_probabilities(dealer_hand, current_prob * probability_of_getting_card, results, cards_left);
            cards_left[c - 2]++;
            dealer_hand.RemoveLastCard();
        }
    }
}

double standing_expected_value(blackjack::Hand player_hand, std::array<double, 5> dealer_probabilities)
{
    double value;
    int player_value = player_hand.Value();
    double prob_of_lossing = 0, prob_of_winning = 0;
    for(int i = player_value+1; i<=23; i++){
        prob_of_lossing += dealer_probabilities[i-17]; 
    } 
    for(int i = 17; i<player_value; i++){
        prob_of_winning += dealer_probabilities[i-17]; 
    } 
    return prob_of_winning - prob_of_lossing;
}

double doubling_expected_value(blackjack::Hand player_hand, std::array<double, 5> dealer_probabilities, std::array<int, 10> cards_left)
{
    double value = 0;
    double n = 0;
    for (int c = 2; c <= 11; c++)
    {
        if (cards_left[c - 2] > 0)
        {
            player_hand.AddCard(c);
            n++;
            value += standing_expected_value(player_hand, dealer_probabilities);
            player_hand.RemoveLastCard();
        }
    }
    return value / n;
}

double hitting_expected_value(blackjack::Hand player_hand, std::array<double, 5> dealer_probabilities, std::array<int, 10> cards_left)
{
    double value = 0.0;
    double n = 0;

    if(player_hand.Value() >= 21) {
        return -1.0;
    }

    for (int c = 2; c <= 11; c++)
    {
        if (cards_left[c - 2] > 0)
        {
            cards_left[c-2]--;
            player_hand.AddCard(c);
            double stand_value = standing_expected_value(player_hand, dealer_probabilities);
            double hit_again_value = hitting_expected_value(player_hand, dealer_probabilities, cards_left);
            value += std::max(stand_value, hit_again_value);
            player_hand.RemoveLastCard();
            cards_left[c-2]++;
        }
    }

    return value / n;
}



int main()
{
    std::array<int, 10> cards_left = {4, 4, 4, 4, 4, 4, 4, 3, 20, 4};
    blackjack::Hand dealer_hand = blackjack::Hand{9};
    double dealer_probabilities[6] = {0, 0, 0, 0, 0, 0};
    calculate_dealer_probabilities(dealer_hand, 1, dealer_probabilities, cards_left);
    std::cout << "Probabilities: \n";
    std::cout << "Total 17: " << dealer_probabilities[0] << ".\n";
    std::cout << "Total 18: " << dealer_probabilities[1] << ".\n";
    std::cout << "Total 19: " << dealer_probabilities[2] << ".\n";
    std::cout << "Total 20: " << dealer_probabilities[3] << ".\n";
    std::cout << "Total 21: " << dealer_probabilities[4] << ".\n";
    std::cout << "Bust: " << dealer_probabilities[5] << ".\n";
    std::cout << dealer_probabilities[0] + dealer_probabilities[1] + dealer_probabilities[2] + dealer_probabilities[3] + dealer_probabilities[4] + dealer_probabilities[5];
}
