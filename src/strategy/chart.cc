#include "chart.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

bool is_whitespace(char c)
{
   return c == ' ' || c == '\v' || c == '\t';
}

void skip_whitespace(const std::string &str, int &i)
{
   while (i < str.length() && is_whitespace(str[i]))
      i++;
}

// Splits a string by whitespaces
std::vector<std::string> split_by_whitespace(const std::string &str)
{
   std::vector<std::string> out;
   int i = 0, start = 0;
   skip_whitespace(str, i);
   if (i >= str.length())
      return {};
   for (;;)
   {
      start = i;
      while (i < str.length() && !is_whitespace(str[i]))
         i++;
      out.push_back(str.substr(start, i - start));
      skip_whitespace(str, i);
      if (i >= str.length())
         break;
   }
   return out;
}

// splits a string by lines, and each line by whitespaces
std::vector<std::vector<std::string>> split(const std::string &str)
{
   std::vector<std::vector<std::string>> ret{};
   std::istringstream iss(str);
   std::string line;
   std::vector<std::string> splited;
   while (std::getline(iss, line))
   {
      splited = split_by_whitespace(line);
      if (splited.size() == 0)
         continue;
      ret.push_back(splited);
   }
   return ret;
}

void remove_comments(std::string &file_content)
{
   int lenght = file_content.length();
   for (int i = 0; i < lenght; i++)
   {
      if (file_content[i] == '#')
      {
         int j = i;
         while (j < lenght && file_content[j] != '\n')
            j++;
         lenght -= j - i;
         file_content.erase(i, j - i);
      }
   }
}

// Returns true if the file was readed succesfully.
bool read_file_to_str(const std::string &path, std::string &file_content)
{
   std::ifstream file_stream;
   std::stringstream buffer;
   file_stream.open(path);
   if (!file_stream.is_open())
      return false;
   buffer << file_stream.rdbuf();
   file_content = buffer.str();
   return true;
}

bj::ChartAction get_action(const std::string &act)
{
   if (act == "DH")
      return bj::ChartAction::DOUBLE_OR_HIT;
   else if (act == "DS")
      return bj::ChartAction::DOUBLE_OR_STAND;
   else if (act == "H")
      return bj::ChartAction::HIT;
   else if (act == "S")
      return bj::ChartAction::STAND;
   else
      return bj::ChartAction::INVALID_ACTION;
}

bj::PairChartAction get_pair_action(const std::string &act)
{
   if (act == "S")
      return bj::PairChartAction::SPLIT;
   else if (act == "D")
      return bj::PairChartAction::DONT_SPLIT;
   else if (act == "SD")
      return bj::PairChartAction::SPLIT_IF_DAS;
   else
      return bj::PairChartAction::INVALID_ACTION;
}

namespace bj
{

   Chart::Chart() {}

   ChartError Chart::Init(std::string path)
   {
      // Chart files have the following format:
      // Everything in a line after # is ignored.
      // First the hard total actions are readed, then soft total actions, then pairs, then surrenders.
      // They have the following format:
      // 11 X (H, S, DS, DH) or (H, S, DS, DH)
      // if the line only has one action, then for all dealer up cards the action is the same
      // else there is one action for each dealer up card.
      // EJ:
      // S S S S H H H H H H H     means stand for dealer 2 to 5 else hit.
      // H                         means hit no matter the dealers card.
      // S S S S DS DS H H H H H H means stand for dealer 2 to 5, double else stand for dealer 6 or 7 else hit.
      std::string file_content;
      if (!read_file_to_str(path, file_content))
         return ChartError::UNABLE_TO_OPEN_FILE;
      remove_comments(file_content);
      auto splited = split(file_content);
      int current_line = 0;
      int hard_total = 20, soft_total = 20;
      // read hard and soft totals:
      while (current_line < splited.size() && (hard_total >= 4 || soft_total >= 12))
      {
         auto line_content = splited[current_line];
         int total = hard_total >= 4 ? hard_total-- : soft_total--;
         switch (line_content.size())
         {
         case 1:
         {
            // if there is only one token in the line,
            //  then it must be an action and that action is taken no matter the dealers card.
            auto action = get_action(line_content[0]);
            if (action == ChartAction::INVALID_ACTION)
               return ChartError::FILE_INVALID;
            for (int i = 2; i <= 11; i++)
               (hard_total >= 4 ? hard_totals : soft_totals).insert({ChartKey{total, i}, action});
            break;
         }
         case 10:
         {
            // if there is ten tokens in the line,
            // then there is an action for each of dealers up card.
            for (int i = 2; i <= 11; i++)
            {
               auto action = get_action(line_content[i - 2]);
               if (action == ChartAction::INVALID_ACTION)
                  return ChartError::FILE_INVALID;
               (hard_total >= 4 ? hard_totals : soft_totals).insert({ChartKey{total, i}, action});
            }
            break;
         }
         default:
            return ChartError::FILE_INVALID;
         }
         current_line++;
      }
      if (hard_total >= 4 || soft_total >= 12)
         return ChartError::FILE_INVALID;

      // read pairs:
      int pair_total = 22;
      while (current_line < splited.size() && pair_total >= 4)
      {
         auto line_content = splited[current_line];
         switch (line_content.size())
         {
         case 1:
         {
            // if there is only one token in the line,
            //  then it must be an action and that action is taken no matter the dealers card.
            auto action = get_pair_action(line_content[0]);
            if (action == PairChartAction::INVALID_ACTION)
               return ChartError::FILE_INVALID;
            for (int i = 2; i <= 11; i++)
               pairs.insert({ChartKey{pair_total, i}, action});
            break;
         }
         case 10:
         {
            // if there is ten tokens in the line,
            // then there is an action for each of dealers up card.
            for (int i = 2; i <= 11; i++)
            {
               auto action = get_pair_action(line_content[i - 2]);
               if (action == PairChartAction::INVALID_ACTION)
                  return ChartError::FILE_INVALID;
               pairs.insert({ChartKey{pair_total, i}, action});
            }
            break;
         }

         default:
            return ChartError::FILE_INVALID;
         }
         current_line++;
         pair_total -= 2;
      }
      if (pair_total >= 4)
         return ChartError::FILE_INVALID;

      if (current_line < splited.size())
      {
         auto line_content = splited[current_line];
         if (line_content.size() < 2)
            return ChartError::FILE_INVALID;
         int player_total = std::stoi(line_content[0]);
         int i = 1;
         while (i < line_content.size())
         {
            surrenders.insert({ChartKey{player_total, std::stoi(line_content[i])}, true});
            i++;
         }
         current_line++;
      }

      return ChartError::NO_ERROR;
   }

   bool Chart::ShouldSurrender(int player_total, int dealer_up)
   {
      if(surrenders.count(ChartKey{player_total, dealer_up}) == 0)
         return false;
      return surrenders[ChartKey{player_total, dealer_up}];
   }

   PairChartAction Chart::ShouldSplit(int player_total, int dealer_up)
   {
      if(pairs.count(ChartKey{player_total, dealer_up}) == 0)
         return PairChartAction::DONT_SPLIT;

      return pairs[ChartKey{player_total, dealer_up}];
   }

   ChartAction Chart::TotalPlay(int player_total, int dealer_up, bool is_soft)
   {
      if((is_soft? soft_totals: hard_totals).count(ChartKey{player_total, dealer_up}) == 0)
         return ChartAction::HIT;
      ChartKey key = ChartKey{player_total, dealer_up};
      return is_soft ? soft_totals[key] : hard_totals[key];
   }
}