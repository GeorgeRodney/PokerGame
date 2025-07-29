#include "Player.hpp"
#include <stdexcept>
#include <iostream>

Player::Player()
{
}

Player::~Player()
{
}

Player::Player(std::string name, int age, std::string catchPhrase)
: Person(name, age, catchPhrase)
, bankroll_(0)
{
}

void Player::requestGame(void) const
{
}

const std::vector<Card>& Player::showCardsToDealer(void) const
{
    return hand_;
}

void Player::addCoinsToBankRoll(const int coins)
{
    bankroll_ += coins;
}

int Player::declareBet(const int bet)
{
    if ((bet > 5) || (bet > bankroll_))
    {
        throw std::runtime_error("You cant bet that much!");
    }
    if (bet < 0)
    {
        throw std::runtime_error("You cant bet nothing!");
    }

    currentBet_ = bet;
    bankroll_ -= bet;
    return bet;
}

void Player::setHand(std::vector<Card>& hand)
{
    hand_ = hand;
}

void Player::lookAtHand(void) const
{
    for (int i{0}; i < hand_.size(); ++i)
    {
        std::cout << "Card " << i << ": "
            << valueToString(hand_[i].getCardId().val) << " of "
             << suitToString(hand_[i].getCardId().suit) << std::endl;
    }
}

int Player::discardXcards(void)
{
    int numCardsToDiscard(0);
    lookAtHand();
    std::cout << "Type 0-5 to discard your cards and 9 to submit" << std::endl;

    int in;
    std::cin >> in;
    while( in != 9)
    {
        numCardsToDiscard++;
        hand_.erase(hand_.begin() + in);

        lookAtHand();

        std::cout << "Type 0-5 to discard your cards and 9 to submit" << std::endl;
        std::cin >> in;
    }

    return numCardsToDiscard;
}

void Player::discard(const int card)
{
    hand_.erase(hand_.begin() + card);
}

void Player::receiveCard(const Card& card)
{
    hand_.push_back(card);
}

int Player::getBankroll(void) const 
{
    return bankroll_;
}