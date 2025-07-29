#pragma once
#include "DeckUtils.hpp"

class Card
{
    private:
        DeckUtils::ID id_;

    public:
        Card();
        ~Card();

        Card(DeckUtils::ID id);
        Card(const Card& c);

        // Getters
        const DeckUtils::ID getCardId(void) const;

        // Debug setters
        void setCardId(const DeckUtils::ID id);

};