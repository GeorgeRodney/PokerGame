#pragma once
#include <stdlib.h>
#include <string>
#include <unordered_map>

class Card;

namespace DeckUtils
{

const int ROYAL_FLUSH_SCALE = 250;
const int STRAIGHT_FLUSH_SCALE = 50;
const int FOUR_KIND_SCALE = 25;
const int FULL_HOUSE_SCALE = 9;
const int FLUSH_SCALE = 6;
const int STRAIGHT_SCALE = 4;
const int THREE_KIND_SCALE = 3;
const int TWO_KIND_SCALE = 2;
const int JACKS_BETTER_SCALE = 1;


enum Suit 
{
    HEART = 0,
    DIAMOND,
    SPADE,
    CLUB,
    NUM_SUIT
};

enum Value
{
    ACE = 1,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    NUM_VALUES
};

struct ID
{
    Value val;
    Suit suit;
};

inline std::string suitToString(Suit suit)
{
    switch(suit)
    {
        case HEART: return "HEART";
        case DIAMOND: return "DIAMOND";
        case SPADE: return "SPADE";
        case CLUB: return "CLUB";
        default: return "UNKOWN_COLOR";
    }
}

inline std::string valueToString(Value value)
{
    switch(value)
    {
        case TWO: return "TWO";
        case THREE: return "THREE";
        case FOUR: return "FOUR";
        case FIVE: return "FIVE";
        case SIX: return "SIX";
        case SEVEN: return "SEVEN";
        case EIGHT: return "EIGHT";
        case NINE: return "NINE";
        case TEN: return "TEN";
        case JACK: return "JACK";
        case QUEEN: return "QUEEN";
        case KING: return "KING";
        case ACE: return "ACE";
        default: return "UNKNOWN_VALUE";
    }
}

std::string cardToFilename(const Card& card);

}