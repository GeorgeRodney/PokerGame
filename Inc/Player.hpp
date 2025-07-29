#pragma once
#include "Person.hpp"
#include <vector>
#include "Card.hpp"

class Player : public Person
{
    private:
        int bankroll_;
        std::vector<Card> hand_;
        int currentBet_;

    public:
        Player();
        ~Player();
        Player(std::string name, int age, std::string catchPhrase);

        void requestGame(void) const;
        const std::vector<Card>& showCardsToDealer(void) const;

        // Setter
        void addCoinsToBankRoll(const int coins);
        int declareBet(const int bet);
        void setHand(std::vector<Card>& hand);

        // 
        void lookAtHand(void) const;
        int discardXcards(void);
        void discard(const int card);
        void receiveCard(const Card& card);
        int getBankroll(void) const;
};