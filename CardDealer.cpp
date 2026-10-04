#include "CardDealer.h"

#include <algorithm>
#include <stdexcept>

CardDealer::CardDealer(int ranks_per_suit)
    : ranks_per_suit_(ranks_per_suit), generator_(std::random_device{}()) {
  if (ranks_per_suit < 1) {
    throw std::invalid_argument("Кількість карт кожної масті має бути додатною");
  }
  TakeNewDeck();
}

void CardDealer::TakeNewDeck() {
  deck_.clear();
  for (Suit suit :
       {Suit::kHearts, Suit::kDiamonds, Suit::kClubs, Suit::kSpades}) {
    for (int rank = 1; rank <= ranks_per_suit_; ++rank) {
      deck_.push_back(Card{rank, suit});
    }
  }
  std::ranges::shuffle(deck_, generator_);
  next_ = 0;
  ++decks_used_;
}

Card CardDealer::operator()() {
  if (next_ == deck_.size()) {
    TakeNewDeck();
  }
  return deck_[next_++];
}
