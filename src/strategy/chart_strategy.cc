#include "chart_strategy.h"

namespace bj
{

    ChartStrategy::ChartStrategy(Chart chart)
    {
        this->chart = chart;
    }

    int ChartStrategy::bet(int min, int max)
    {
        return min;
    }

    PlayerAction ChartStrategy::play(Hand player_hand, Card dealer_card, PlayOptions options)
    {
        if (options.can_surrender && !player_hand.IsSoft() && chart.ShouldSurrender(player_hand.Value(), dealer_card))
            return PlayerAction::SURRENDER;

        if (options.can_split && player_hand.CanSplit())
        {
            switch (chart.ShouldSplit(player_hand.RawValue(), dealer_card))
            {
            case PairChartAction::SPLIT_IF_DAS:
                if (options.can_DAS)
                    return PlayerAction::SPLIT;
            case PairChartAction::SPLIT:
                return PlayerAction::SPLIT;
            }
        }

        switch (chart.TotalPlay(player_hand.Value(), dealer_card, player_hand.IsSoft()))
        {

        case ChartAction::HIT:
            return PlayerAction::HIT;

        case ChartAction::STAND:
            return PlayerAction::STAND;

        case ChartAction::DOUBLE_OR_HIT:
            if (options.can_double)
                return PlayerAction::DOUBLE;
            else
                return PlayerAction::HIT;

        case ChartAction::DOUBLE_OR_STAND:
            if (options.can_double)
                return PlayerAction::DOUBLE;
            else
                return PlayerAction::STAND;

        default:
            return PlayerAction::STAND;
        }

    }

    bool ChartStrategy::wants_insurance()
    {
        return false;
    }

    void ChartStrategy::see_card(Card card)
    {

    }

    void ChartStrategy::see_cards(std::vector<Card> cards)
    {

    }

    void ChartStrategy::on_shuffle(int decks)
    {
        
    }

}