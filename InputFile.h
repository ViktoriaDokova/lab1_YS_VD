#pragma once

#include <string>

struct InputData {
  int ranks_per_suit = 0;
  long long card_count = 0;
};

// Input file format: two integers, one per line (empty lines are ignored):
//   ranks per suit, in [1, 1000];
//   number of cards to deal, in [1, 10000000].
InputData ReadInputFile(const std::string& path);
