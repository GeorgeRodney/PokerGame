#include "Card.hpp"

Card::Card()
{
}

Card::~Card()
{
}

Card::Card(DeckUtils::ID id)
: id_(id)
{
}

Card::Card(const Card& c)
: id_(c.id_)
{
}

const DeckUtils::ID Card::getCardId(void) const
{
    return id_;
}

void Card::setCardId(const DeckUtils::ID id)
{
    id_ = id;
}