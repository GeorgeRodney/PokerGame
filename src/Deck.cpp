#include "Deck.hpp"
#include "DeckUtils.hpp"
#include "Card.hpp"
#include <algorithm>
#include <random>
#include <iostream>

Deck::Deck()
: g(rd())
{
}

Deck::~Deck()
{
}

void Deck::initialize(void)
{
    addCardsBackToDeck();
    // for (int i{0}; i < deck_.size(); ++i)
    // {
    //     std::cout << valueToString(deck_[i].getCardId().val)
    //                 << " of " << suitToString(deck_[i].getCardId().suit) << std::endl;
    // }
    shuffle();

    // for (int i{0}; i < deck_.size(); ++i)
    // {
    //     std::cout << valueToString(deck_[i].getCardId().val)
    //                 << " of " << suitToString(deck_[i].getCardId().suit) << std::endl;
    // }
}

const Card Deck::drawCard(void)
{
    if (deck_.empty())
    {
        throw std::runtime_error("Deck is empty. Cant draw another.");
    }
    Card temp = deck_.back();
    deck_.pop_back();
    return temp;
}

const std::vector<Card> Deck::drawHand(void)
{
    if (deck_.size() < 5)
    {
        throw std::runtime_error("Deck is not larger enough to draw five.");
    }   
    std::vector<Card> hand;
    auto iterator = deck_.end() - 5;
    std::copy(iterator, deck_.end(), std::back_inserter(hand));
    deck_.erase(deck_.end()-5, deck_.end());
    return hand;
}

void Deck::deckSize(void) const
{
    std::cout << "Cards in deck: " << deck_.size() << std::endl;
}

void Deck::addCardsBackToDeck(void)
{
    deck_.clear();
    for (int suit{0}; suit < DeckUtils::NUM_SUIT; ++suit)
    {
        for (int val{1}; val < DeckUtils::NUM_VALUES; ++val)
        {
            DeckUtils::ID cardId;
            cardId.suit = static_cast<DeckUtils::Suit>(suit);
            cardId.val = static_cast<DeckUtils::Value>(val);
            Card card(cardId);
            deck_.push_back(card);
        }
    }
}

void Deck::shuffle(void)
{
    std::shuffle(deck_.begin(), deck_.end(), g);
}