#ifndef CARD_H_
#define CARD_H_

#include <compare>

enum class Suit { kHearts, kDiamonds, kClubs, kSpades };

// A playing card. Cards are compared by rank only; suit is ignored.
struct Card {
  int rank = 1;
  Suit suit = Suit::kHearts;

  // Weak ordering: cards of equal rank but different suits are equivalent.
  std::weak_ordering operator<=>(const Card& other) const {
    return rank <=> other.rank;
  }
};

#endif  // CARD_H_
