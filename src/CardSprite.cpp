#include "CardSprite.hpp"

CardSprite::CardSprite()
{
}

CardSprite::~CardSprite()
{
}

CardSprite::CardSprite(const std::string& imgFile
                        , const int COL
                        , const int ROW)
{
    if(!texture_.loadFromFile(imgFile))
    {
        throw std::runtime_error("Sprite image didnt load");
    }
    sprite_.setTexture(texture_);
    sprite_.setPosition(COL - sprite_.getLocalBounds().getSize().x/2, ROW);
}

void CardSprite::loadCardImage(const std::string& fileName)
{
    
    if(!texture_.loadFromFile(fileName))
    {
        throw std::runtime_error("Card texture didnt load!");
    }
    sprite_.setTexture(texture_);
    
}