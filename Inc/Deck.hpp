#pragma once
#include <vector>
#include <random>

class Card;

class Deck
{
    private:
        std::vector<Card> deck_;
        std::random_device rd;
        std::mt19937 g;


    public:
        Deck();
        ~Deck();

        void initialize(void);

        // Getters
        const Card drawCard(void);
        const std::vector<Card> drawHand(void);
        void deckSize(void) const;
        void addCardsBackToDeck(void);
        void shuffle(void);

};