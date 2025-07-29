#pragma once
#include "Person.hpp"
#include "Deck.hpp"
#include <vector>

class Card;
class Player;

class Dealer : public Person
{
    private:
        std::string dealingTo_;
        Deck* pDealerDeck_;
        int currentBet_;
        std::vector<Card> hand_;
        int nCardPlayerDicard_;

    public:
        Dealer();
        ~Dealer();

        Dealer(std::string name, int age, std::string catchPhrase);
        int judgeHand(const std::vector<Card> hand);
        void shuffleDeck(void);

        // Setters
        void setDealingTo(const std::string player);
        void setDeck(Deck& deck);
        void setCurrentBet(const int currentBet);

        // Getters
        const std::vector<Card> dealHand(void);
        const Card dealCard(void);
        void deckSize(void) const;
        int getNumCardsPlayerDiscard(void) const;

        // Judge
        bool isRoyalFlush(void) const;
        bool isStraightFlush(void) const;
        bool isFourOfAKind(void) const;
        bool isFullHouse(void) const;
        bool isFlush(void) const;
        bool isStraight(void) const;
        bool isThreeOfAKind(void) const;
        bool isTwoPair(void) const;
        bool isJacksOrBetter(void) const;

        void receiveDiscard(const int nCards);


};