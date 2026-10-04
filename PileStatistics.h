#ifndef PILE_STATISTICS_H_
#define PILE_STATISTICS_H_

#include <cstddef>
#include <map>
#include <ostream>
#include <vector>

#include "CardDealer.h"

// Statistics of pile lengths.
struct PileStatistics {
  std::map<int, double> percent_by_length;  // Length -> % of piles.
  std::size_t pile_count = 0;
  int most_frequent_length = 0;
  double mean_length = 0.0;
  double median_length = 0.0;
};

// Deals `card_count` cards and returns the lengths of all piles.
// A pile grows while each card is higher than the previous one.
// Throws std::invalid_argument if card_count < 1.
std::vector<int> DealPiles(CardDealer& dealer, long long card_count);

// Computes statistics for `lengths`. `max_length` is the longest possible
// pile (equal to the number of ranks per suit).
// Throws std::invalid_argument if `lengths` is empty.
PileStatistics ComputeStatistics(std::vector<int> lengths, int max_length);

void PrintStatistics(const PileStatistics& stats, std::ostream& out);

#endif  // PILE_STATISTICS_H_
