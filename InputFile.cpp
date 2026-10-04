#include "InputFile.h"

#include <format>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace {

constexpr long long MAX_RANKS = 1000;
constexpr long long MAX_CARDS = 10'000'000;

struct Line {
  int number;
  std::string text;
};

// Line numbers are kept so that error messages point to the right line.
std::vector<Line> ReadNonEmptyLines(std::ifstream& file) {
  std::vector<Line> lines;
  std::string text;
  for (int number = 1; std::getline(file, text); ++number) {
    if (text.find_first_not_of(" \t\r") != std::string::npos) {
      lines.push_back({number, text});
    }
  }
  return lines;
}

long long ParseNumber(const Line& line, const std::string& name, long long min,
                      long long max) {
  std::istringstream in(line.text);
  long long value = 0;
  char extra = 0;
  // Fails on non-numbers and overflow; a second read catches "12abc", "1.5".
  if (!(in >> value) || (in >> extra)) {
    throw std::runtime_error(
        std::format("line {}: {} must be a single integer, got \"{}\"",
                    line.number, name, line.text));
  }
  if (value < min || value > max) {
    throw std::runtime_error(std::format("line {}: {} must be in [{}, {}], got {}",
                                         line.number, name, min, max, value));
  }
  return value;
}

}

InputData ReadInputFile(const std::string& path) {
  std::ifstream file(path);
  if (!file) {
    throw std::runtime_error(std::format("cannot open input file \"{}\"", path));
  }

  std::vector<Line> lines = ReadNonEmptyLines(file);
  if (lines.size() != 2) {
    throw std::runtime_error(
        std::format("file \"{}\" must contain 2 numbers, found {} non-empty lines",
                    path, lines.size()));
  }

  InputData data;
  data.ranks_per_suit =
      static_cast<int>(ParseNumber(lines[0], "ranks per suit", 1, MAX_RANKS));
  data.card_count = ParseNumber(lines[1], "number of cards", 1, MAX_CARDS);
  return data;
}
