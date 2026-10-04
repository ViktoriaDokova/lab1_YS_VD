#include "CardDealer.h"

#include <algorithm>
#include <stdexcept>

CardDealer::CardDealer(int ranks)
    : ranks_per_suit(ranks), generator(std::random_device{}()) {
  if (ranks < 1) {
    throw std::invalid_argument("Ranks per suit must be positive");
  }
  TakeNewDeck();
}

void CardDealer::TakeNewDeck() {
  deck.clear();
  for (Suit suit : {Suit::Hearts, Suit::Diamonds, Suit::Clubs, Suit::Spades}) {
    for (int rank = 1; rank <= ranks_per_suit; ++rank) {
      deck.push_back(Card{rank, suit});
    }
  }
  std::ranges::shuffle(deck, generator);
  next_index = 0;
  ++decks_used;
}

Card CardDealer::operator()() {
  if (next_index == deck.size()) {
    TakeNewDeck();
  }
  return deck[next_index++];
}
