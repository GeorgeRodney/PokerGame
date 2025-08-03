#pragma once
#include <SFML/Graphics.hpp>

class CardSprite
{
    private:
        sf::Texture texture_;
        sf::Sprite sprite_;

    public:
        CardSprite();
        ~CardSprite();
        CardSprite(const std::string& imgFile, const int COL, const int ROW);

    const sf::Sprite& getSprite(void) const { return sprite_; }
    void loadCardImage(const std::string& fileName);

};

