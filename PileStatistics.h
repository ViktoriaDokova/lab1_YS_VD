#pragma once

#include <cstddef>
#include <map>
#include <ostream>
#include <vector>

#include "CardDealer.h"

struct PileStatistics {
  std::map<int, double> percent_by_length;
  std::size_t pile_count = 0;
  int most_frequent_length = 0;
  double mean_length = 0.0;
  double median_length = 0.0;
};

std::vector<int> DealPiles(CardDealer& dealer, long long card_count);

// max_length is the longest possible pile, i.e. ranks per suit.
PileStatistics ComputeStatistics(std::vector<int> lengths, int max_length);

void PrintStatistics(const PileStatistics& stats, std::ostream& out);
