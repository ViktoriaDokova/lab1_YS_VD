#include "PileStatistics.h"

#include <algorithm>
#include <format>
#include <functional>
#include <numeric>
#include <stdexcept>

std::vector<int> DealPiles(CardDealer& dealer, long long card_count) {
  if (card_count < 1) {
    throw std::invalid_argument("Кількість карт для роздачі має бути додатною");
  }

  std::vector<int> lengths;
  Card previous = dealer();
  int current_length = 1;

  for (long long i = 1; i < card_count; ++i) {
    Card card = dealer();
    if (card > previous) {
      ++current_length;
    } else {
      lengths.push_back(current_length);
      current_length = 1;
    }
    previous = card;
  }
  lengths.push_back(current_length);  // The last, unfinished pile.
  return lengths;
}

PileStatistics ComputeStatistics(std::vector<int> lengths, int max_length) {
  if (lengths.empty()) {
    throw std::invalid_argument("Немає жодної стопки для аналізу");
  }

  PileStatistics stats;
  stats.pile_count = lengths.size();

  // Include every possible length, even those that never occurred.
  std::map<int, int> counts;
  for (int length = 1; length <= max_length; ++length) {
    counts[length] = 0;
  }
  for (int length : lengths) {
    ++counts[length];
  }

  for (const auto& [length, count] : counts) {
    stats.percent_by_length[length] = 100.0 * count / stats.pile_count;
  }

  auto most_frequent = std::ranges::max_element(
      counts, [](const auto& a, const auto& b) { return a.second < b.second; });
  stats.most_frequent_length = most_frequent->first;

  long long sum =
      std::accumulate(lengths.begin(), lengths.end(), 0LL, std::plus<>{});
  stats.mean_length = static_cast<double>(sum) / stats.pile_count;

  std::ranges::sort(lengths, std::less<>{});
  std::size_t middle = lengths.size() / 2;
  stats.median_length = lengths.size() % 2 == 1
                            ? lengths[middle]
                            : (lengths[middle - 1] + lengths[middle]) / 2.0;
  return stats;
}

void PrintStatistics(const PileStatistics& stats, std::ostream& out) {
  out << std::format("\nУсього стопок: {}\n\n", stats.pile_count);
  out << " Довжина |  % стопок\n";
  out << "---------+-----------\n";
  for (const auto& [length, percent] : stats.percent_by_length) {
    out << std::format("{:>8} | {:>8.3f}%\n", length, percent);
  }
  out << std::format("\nНайчастіша довжина стопки: {}\n",
                           stats.most_frequent_length);
  out << std::format("Середня довжина стопки:    {:.4f}\n",
                           stats.mean_length);
  out << std::format("Медіанна довжина стопки:   {}\n",
                           stats.median_length);
}
