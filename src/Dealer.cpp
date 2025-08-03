#include "Dealer.hpp"
#include "Card.hpp"
#include <algorithm>
#include <iostream>
#include <stdexcept>

Dealer::Dealer()
{
}

Dealer::~Dealer()
{
}

Dealer::Dealer(std::string name, int age, std::string catchPhrase)
: Person(name, age, catchPhrase)
, pDealerDeck_(nullptr)
, currentBet_(0)
, hand_()
, nCardPlayerDicard_(0)
{
}

int Dealer::judgeHand(const std::vector<Card> hand)
{
    hand_ = hand;

    // The order here matters. Go from high to low to avoid bailing out if 
    // lesser condition has been met
    if (isRoyalFlush()) // Good
    {
        return currentBet_ + currentBet_ * DeckUtils::ROYAL_FLUSH_SCALE;
        std::cout << "Won royal flush" << std::endl;
    }
    else if (isStraightFlush()) // Good
    {
        return currentBet_ + currentBet_ * DeckUtils::STRAIGHT_FLUSH_SCALE;
        std::cout << "Won straight flush" << std::endl;
    }
    else if (isFourOfAKind()) // Good
    {
        return currentBet_ + currentBet_ * DeckUtils::FOUR_KIND_SCALE;
        std::cout << "Won four of kind" << std::endl;
    }
    else if (isFullHouse()) // Good
    {
        return currentBet_ + currentBet_ * DeckUtils::FULL_HOUSE_SCALE;
        std::cout << "Won full house" << std::endl;
    }
    else if (isStraight()) // Good
    {
        return currentBet_ + currentBet_ * DeckUtils::STRAIGHT_SCALE;
        std::cout << "Won straight" << std::endl;
    }
    else if (isThreeOfAKind()) // Good
    {
        return currentBet_ + currentBet_ * DeckUtils::THREE_KIND_SCALE;
        std::cout << "Won thee of a kind" << std::endl;
    }
    else if (isTwoPair()) // Good
    {
        return currentBet_ + currentBet_ * DeckUtils::TWO_KIND_SCALE;
        std::cout << "Won with two pair" << std::endl;
    }
    else if (isJacksOrBetter()) // Good
    {
        return currentBet_ + currentBet_ * DeckUtils::JACKS_BETTER_SCALE;
        std::cout << "Won with jacks or better" << std::endl;
    }
    else
    {
        this->emote();
    }

    return 0;
}

void Dealer::shuffleDeck(void)
{
    pDealerDeck_->initialize();
}

void Dealer::setDealingTo(const std::string player)
{
     dealingTo_ = player;
}

void Dealer::setDeck(Deck& deck)
{
    pDealerDeck_ = &deck;
}

void Dealer::setCurrentBet(const int currentBet)
{
    currentBet_ = currentBet;
}

const std::vector<Card> Dealer::dealHand(void)
{
    return pDealerDeck_->drawHand();
}

const Card Dealer::dealCard(void)
{
    return pDealerDeck_->drawCard();
}

void Dealer::deckSize(void) const
{
    pDealerDeck_->deckSize();
}

int Dealer::getNumCardsPlayerDiscard(void) const
{
    return nCardPlayerDicard_;
}

bool Dealer::isRoyalFlush(void) const
{
    bool gotIt(true);

    for (int card{0}; card < hand_.size(); ++card)
    {
        if (hand_[card].getCardId().val == DeckUtils::TEN)
        {
            gotIt = (gotIt & true);
        }
        else if (hand_[card].getCardId().val == DeckUtils::JACK)
        {
            gotIt = (gotIt & true);
        }
        else if (hand_[card].getCardId().val == DeckUtils::QUEEN)
        {
            gotIt = (gotIt & true);
        }
        else if (hand_[card].getCardId().val == DeckUtils::KING)
        {
            gotIt = (gotIt & true);
        }
        else if (hand_[card].getCardId().val == DeckUtils::ACE)
        {
            gotIt = (gotIt & true);
        }
        else 
        {
            return (gotIt & false);
        }
    }

    DeckUtils::Suit startSuit = hand_[0].getCardId().suit;
    for (int card{1}; card < hand_.size(); ++card)
    {
        if(hand_[card].getCardId().suit == startSuit)
        {
            gotIt = (gotIt & true);
        }
        else 
        {
            return (gotIt & false);
        }
    }

    return gotIt;


}

bool Dealer::isStraightFlush(void) const
{
    bool gotIt(true);

    // Check for straight
    gotIt = isStraight();

    // Check for flush
    gotIt = isFlush();

    return gotIt;
}

bool Dealer::isFourOfAKind(void) const
{
    bool gotIt(false);

    // Sort the card values
    std::vector<int> value;
    for (int card{0}; card < hand_.size(); ++card)
    {
        value.push_back(static_cast<int>(hand_[card].getCardId().val));
    }
    std::sort(value.begin(), value.end());

    // Check for same same
    for (int card{0}; card < value.size(); ++card)
    {
        int duplicates(0);
        for (int otherCard{0}; otherCard < value.size(); ++otherCard)
        {
            if (card == otherCard)
            {
                continue; // Only check for similarities if its another card
            }

            if (value[card] == value[otherCard])
            {
                duplicates++;
            }
        }

        if (duplicates == 3)
        {
            return true;
        }
    }

    return gotIt;
}

bool Dealer::isFullHouse(void) const
{
    bool gotIt(false);

    // Sort the card values
    std::vector<int> value;
    for (int card{0}; card < hand_.size(); ++card)
    {
        value.push_back(static_cast<int>(hand_[card].getCardId().val));
    }
    std::sort(value.begin(), value.end());

    // 1. Check for a three of a kind
    // 2. Hold onto the index values
    // 3. If no three of kind leave with false
    // 4. If I have a three of a kind remove the three cards
    // 5. Then check to be sure the remaining two are the same.
    std::vector<int> sameIdxs;
    bool anyThreeOfKind(false);
    for (int card{0}; card < value.size(); ++card)
    {
        int duplicates(0);
        sameIdxs.push_back(card);
        for (int otherCard{0}; otherCard < value.size(); ++otherCard)
        {
            if (card == otherCard)
            {
                continue; // Only check for similarities if its another card
            }

            if (value[card] == value[otherCard])
            {
                duplicates++;
                // 2. Hold onto indexes
                sameIdxs.push_back(otherCard);
            }
        }

        // 1. If we have a three of a kind
        if (duplicates == 2)
        {
            gotIt = true;
            anyThreeOfKind = true;
            break;
        }
        else 
        {
            sameIdxs.clear();
        }
    }

    // 3. Leave if no three of kind found
    if(anyThreeOfKind == false)
    {
        return (gotIt & false);
    }

    // 4. Remove three of kind cards
    std::vector<int> downSampled;
    for (int card{0}; card < value.size(); ++card)
    {
        if ( std::find(sameIdxs.begin(), sameIdxs.end(), card) == sameIdxs.end())
        {
            downSampled.push_back(value[card]);
        }
    }

    // 5. Check to see if remaining cards are the same
    if (downSampled[0] == downSampled[1])
    {
        return (gotIt & true);
    }
    else
    {
        return (gotIt & false);
    }
    
    return gotIt;
}

bool Dealer::isFlush(void) const
{
    bool gotIt(true);
 
    DeckUtils::Suit startSuit = hand_[0].getCardId().suit;
    for (int card{1}; card < hand_.size(); ++card)
    {
        if(hand_[card].getCardId().suit == startSuit)
        {
            gotIt = (gotIt & true);
        }
        else 
        {
            return (gotIt & false);
        }
    }

    return gotIt;
}

//>---------------------------------------------------------------------------------------------------<
//  Citation    : ChatGPT, July 26 2025
//
//  Prompt      : How do I judge if a hand is a straight without a zillion lines of if checks
//  Outcome     : I took the ChatGPT idea of sorting the values but not the implementation
//>---------------------------------------------------------------------------------------------------<
bool Dealer::isStraight(void) const
{
    bool gotIt(true);

    // Sort the card values
    std::vector<int> value;
    for (int card{0}; card < hand_.size(); ++card)
    {
        value.push_back(static_cast<int>(hand_[card].getCardId().val));
    }
    std::sort(value.begin(), value.end());

    // Check for straight
    for (int card{0}; card < hand_.size()-1; ++card)
    {
        if (value[card] == (value[card+1] - 1))
        {
            gotIt = (gotIt & true);
        }
        else
        {
            return (gotIt & false);
        }
    }

    return gotIt;
}

bool Dealer::isThreeOfAKind(void) const
{
    bool gotIt(false);

    // Sort the card values
    std::vector<int> value;
    for (int card{0}; card < hand_.size(); ++card)
    {
        value.push_back(static_cast<int>(hand_[card].getCardId().val));
    }
    std::sort(value.begin(), value.end());

    // Check for same same
    for (int card{0}; card < value.size(); ++card)
    {
        int duplicates(0);
        for (int otherCard{0}; otherCard < value.size(); ++otherCard)
        {
            if (card == otherCard)
            {
                continue; // Only check for similarities if its another card
            }

            if (value[card] == value[otherCard])
            {
                duplicates++;
            }
        }

        if (duplicates == 2)
        {
            return true;
        }
    }

    return gotIt;
}

bool Dealer::isTwoPair(void) const
{
    bool gotIt(false);

    // Sort the card values
    std::vector<int> value;
    for (int card{0}; card < hand_.size(); ++card)
    {
        value.push_back(static_cast<int>(hand_[card].getCardId().val));
    }
    std::sort(value.begin(), value.end());

    // 1. Check for a two of a kind
    // 2. Hold onto the index values
    // 3. If no two of kind leave with false
    // 4. If I have a two of a kind remove the two cards
    // 5. Then check if there is another two of kind remianing.
    std::vector<int> sameIdxs;
    bool anyTwoOfkind(false);
    for (int card{0}; card < value.size(); ++card)
    {
        int duplicates(0);
        sameIdxs.push_back(card);
        for (int otherCard{0}; otherCard < value.size(); ++otherCard)
        {
            if (card == otherCard)
            {
                continue; // Only check for similarities if its another card
            }

            if (value[card] == value[otherCard])
            {
                duplicates++;
                // 2. Hold onto indexes
                sameIdxs.push_back(otherCard);
            }
        }

        // 1. If we have a two of a kind
        if (duplicates == 1)
        {
            gotIt = true;
            anyTwoOfkind = true;
            break;
        }
        else 
        {
            sameIdxs.clear();
        }
    }

    // 3. Leave if no three of kind found
    if(anyTwoOfkind == false)
    {
        return (gotIt & false);
    }

    // 4. Remove two of kind cards
    std::vector<int> downSampled;
    for (int card{0}; card < value.size(); ++card)
    {
        if (std::find(sameIdxs.begin(), sameIdxs.end(), card) == sameIdxs.end())
        {
            downSampled.push_back(value[card]);
        }
    }

    // 5. Check to see if two of kind in remaining cards
    // sameIdxs.clear();
    anyTwoOfkind = false;
    for (int card{0}; card < downSampled.size(); ++card)
    {
        int duplicates(0);
        // sameIdxs.push_back(card);
        for (int otherCard{0}; otherCard < downSampled.size(); ++otherCard)
        {
            if (card == otherCard)
            {
                continue; // Only check for similarities if its another card
            }

            if (downSampled[card] == downSampled[otherCard])
            {
                duplicates++;
                // sameIdxs.push_back(otherCard);
            }
        }
        if (duplicates == 1)
        {
            return (gotIt & true);
        }
        else 
        {
            // sameIdxs.clear();
        }
    }

    return (gotIt & false);
}

bool Dealer::isJacksOrBetter(void) const
{
    // 1. Look to see if there is exactly one pair
    // 2. If there is no single pair, depart false
    // 3. If one pair check for value to be Jack+
    bool gotIt(true);

    // Sort the card values
    std::vector<int> value;
    for (int card{0}; card < hand_.size(); ++card)
    {
        value.push_back(static_cast<int>(hand_[card].getCardId().val));
    }
    std::sort(value.begin(), value.end());

    std::vector<int> sameIdxs;
    int numPairs(0);
    for (int card{0}; card < value.size(); ++card)
    {
        int duplicates(0);
        sameIdxs.push_back(card);
        for (int otherCard{0}; otherCard < value.size(); ++otherCard)
        {
            if (card == otherCard)
            {
                continue; // Only check for similarities if its another card
            }

            if (value[card] == value[otherCard])
            {
                duplicates++;
                sameIdxs.push_back(otherCard);
            }
        }

        // Count how many pairs
        if (duplicates == 1)
        {
            numPairs++;
            break;
        }
        else
        {
            sameIdxs.clear();
        }
    }

    // If there are more or less than a single pair, bail
    if (numPairs != 1)
    {
        return (gotIt & false);
    }
    
    // If there is one pair check for jack+
    if ((value[sameIdxs[0]] >= DeckUtils::JACK) && (value[sameIdxs[1]] >= DeckUtils::JACK))
    {
        return (gotIt & true);
    }
    else 
    {
        gotIt = (gotIt & false);
    }

    return gotIt;

    
}

void Dealer::receiveDiscard(const int nCards)
{
    nCardPlayerDicard_++;
}

void Dealer::resetGame(void)
{
    shuffleDeck();
    nCardPlayerDicard_ = 0;
    currentBet_ = 0;
}