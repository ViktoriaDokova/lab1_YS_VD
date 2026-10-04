#ifndef CARD_DEALER_H_
#define CARD_DEALER_H_

#include <cstddef>
#include <random>
#include <vector>

#include "Card.h"

// Deals cards from a shuffled deck of 4 suits. When the deck runs out,
// a new one is taken and shuffled.
//
// Example:
//   CardDealer dealer(13);
//   Card card = dealer();
class CardDealer {
 public:
  // Throws std::invalid_argument if ranks_per_suit < 1.
  explicit CardDealer(int ranks_per_suit);

  // Returns the next card from the deck.
  Card operator()();

  int ranks_per_suit() const { return ranks_per_suit_; }
  int decks_used() const { return decks_used_; }

 private:
  void TakeNewDeck();

  int ranks_per_suit_;
  std::vector<Card> deck_;
  std::size_t next_ = 0;  // Index of the next card to deal.
  int decks_used_ = 0;
  std::mt19937 generator_;
};

#endif  // CARD_DEALER_H_
