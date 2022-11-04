#ifndef CHART_H
#define CHART_H

#include <map>
#include <string>

namespace bj {

   enum class ChartError {
      NO_ERROR,
      UNABLE_TO_OPEN_FILE,
      FILE_INVALID,
   };

   enum class ChartAction {
      INVALID_ACTION,
      HIT,
      STAND,
      DOUBLE_OR_STAND,  // Double if allowed else stand.
      DOUBLE_OR_HIT,    // Double if allowed else hit.
   };

   enum class PairChartAction {
      INVALID_ACTION,
      DONT_SPLIT,   // Dont split the pair.
      SPLIT,        // Split the pair.
      SPLIT_IF_DAS, // Split the pair only if doubling after spliting is allowed.
   };

   struct ChartKey {
      int player_total, dealer_up;
      inline bool operator< (const ChartKey& rhs) const { 
         return (player_total < rhs.player_total) || (dealer_up < rhs.dealer_up); 
      }
      inline bool operator== (const ChartKey& rhs) const { 
         return (player_total == rhs.player_total) && (dealer_up == rhs.dealer_up); 
         }
   };

   class Chart {
   public:

      Chart();

      // Tries to create the chart with the information in the file at path.
      // Returns NO_ERROR if it initialized ok,
      // else it returns the error that occurred.
      ChartError Init(std::string path);

      bool ShouldSurrender(int player_total, int dealer_up);
      PairChartAction ShouldSplit(int player_total, int dealer_up);
      ChartAction TotalPlay(int player_total, int dealer_up, bool is_soft);

   private:
      // maps totals to actions, one for hard_totals, and another for soft_totals.
      std::map<ChartKey, ChartAction> hard_totals, soft_totals;
      // maps pairs to actions, the key is the added value of the pair.
      // EJ: if the key is 12 and the value is SPLIT, that means that a pair of 6s should be split.
      std::map<ChartKey, PairChartAction> pairs;  
      // maps hard totals to surrender.
      std::map<ChartKey, bool> surrenders;
   };

}

#endif