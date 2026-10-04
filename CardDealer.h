#pragma once

#include <cstddef>
#include <random>
#include <vector>

#include "Card.h"

// Deals cards from a shuffled 4-suit deck. When the deck runs out,
// a new one is taken and shuffled.
class CardDealer {
 public:
  explicit CardDealer(int ranks);

  Card operator()();

  int DecksUsed() const { return decks_used; }

 private:
  void TakeNewDeck();

  int ranks_per_suit;
  std::vector<Card> deck;
  std::size_t next_index = 0;
  int decks_used = 0;
  std::mt19937 generator;
};
