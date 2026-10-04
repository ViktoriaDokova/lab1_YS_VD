// Lab 1, Variant 4
// Authors: Dokova Viktoria and Yaroslav Starchenko K-28 

#include <exception>
#include <format>
#include <fstream>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "CardDealer.h"
#include "InputFile.h"
#include "PileStatistics.h"

namespace {

constexpr long long EXPERIMENT_CARDS = 1'000'000;

void RunSingleDeal(const InputData& data, std::ostream& out) {
  CardDealer dealer(data.ranks_per_suit);
  PileStatistics stats = ComputeStatistics(
      DealPiles(dealer, data.card_count), data.ranks_per_suit);

  out << std::format("Ranks per suit: {}\n", data.ranks_per_suit);
  out << std::format("Cards dealt: {}\n", data.card_count);
  out << std::format("Decks used: {}\n", dealer.DecksUsed());
  PrintStatistics(stats, out);
}

void RunExperiment(std::ostream& out) {
  const std::vector<int> ranks_to_test = {1, 2, 3, 4, 6, 9, 13, 20, 50, 100, 500};

  out << std::format("\nExperiment ({} cards for each value):\n",
                     EXPERIMENT_CARDS);
  for (int ranks : ranks_to_test) {
    CardDealer dealer(ranks);
    PileStatistics stats =
        ComputeStatistics(DealPiles(dealer, EXPERIMENT_CARDS), ranks);
    out << std::format("ranks = {}: mean = {:.4f}, median = {}\n", ranks,
                       stats.mean_length, stats.median_length);
  }
}

}  

int main(int argc, char* argv[]) {
  if (argc > 3) {
    std::cerr << "Usage: cards [input_file] [output_file]\n";
    return 1;
  }
  const std::string input_path = argc > 1 ? argv[1] : "input.txt";
  const std::string output_path = argc > 2 ? argv[2] : "output.txt";

  try {
    InputData data = ReadInputFile(input_path);

    std::ofstream out(output_path);
    if (!out) {
      throw std::runtime_error(
          std::format("cannot create output file \"{}\"", output_path));
    }
    RunSingleDeal(data, out);
    RunExperiment(out);

    std::cout << std::format("Done. Results written to \"{}\"\n", output_path);
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << '\n';
    return 1;
  }
  return 0;
}
