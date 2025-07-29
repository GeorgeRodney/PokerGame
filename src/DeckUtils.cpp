#include "Card.hpp"
#include "DeckUtils.hpp"

namespace DeckUtils
{

std::string cardToFilename(const Card& card)
{
    static const std::unordered_map<Suit, std::string> suitMap = {
        {Suit::SPADE, "spades"},
        {Suit::HEART, "hearts"},
        {Suit::DIAMOND, "diamonds"},
        {Suit::CLUB, "clubs"}
    };

    static const std::unordered_map<Value, std::string> valueMap = {
        {Value::ACE, "A"},
        {Value::TWO, "02"}, {Value::THREE, "03"}, {Value::FOUR, "04"},
        {Value::FIVE, "05"}, {Value::SIX, "06"}, {Value::SEVEN, "07"},
        {Value::EIGHT, "08"}, {Value::NINE, "09"}, {Value::TEN, "10"},
        {Value::JACK, "J"}, {Value::QUEEN, "Q"}, {Value::KING, "K"}
    };

    std::string basePath = "../resources/large/";
    return basePath + "card_" + suitMap.at(static_cast<Suit>(card.getCardId().suit)) + "_" + valueMap.at(card.getCardId().val) + ".png";
}





}