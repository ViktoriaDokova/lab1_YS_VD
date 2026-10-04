#pragma once

#include <compare>

enum class Suit { Hearts, Diamonds, Clubs, Spades };

struct Card {
  int rank = 1;
  Suit suit = Suit::Hearts;

  // Compared by rank only, so cards of equal rank and different suits are
  // equivalent but not identical - hence weak_ordering.
  std::weak_ordering operator<=>(const Card& other) const {
    return rank <=> other.rank;
  }
};
