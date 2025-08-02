#pragma once
#include <SFML/Graphics.hpp>

class Button
{
    private:
        sf::RectangleShape square_{};
        sf::Text text_{};

        const int BTN_OUTLINE = 5;
        const int TEXT_THICK = 30;

    public:
        Button();
        ~Button();
        Button(const int width
                , const int height
                , const int col
                , const int row
                , const sf::Color recColor
                , const sf::Font font
                , const std::string& text
                );

        const sf::RectangleShape& getRect(void) const { return square_; }
        const sf::Text& getText(void) const { return text_; }

        void setFillColor(const sf::Color& c);
};  