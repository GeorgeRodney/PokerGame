#include "Button.hpp"

Button::Button()
{
}

Button::~Button()
{
}

Button::Button(const int width
                , const int height
                , const int col
                , const int row
                , const sf::Color recColor
                , const sf::Font& font
                , const std::string& text)
: text_(text, font, TEXT_THICK)
{
    square_.setSize(sf::Vector2f(width, height));
    square_.setPosition(col - width/2, row-height/2);
    square_.setFillColor(recColor);
    square_.setOutlineColor(sf::Color::Black);
    square_.setOutlineThickness(BTN_OUTLINE);

    text_.setPosition(col-width/2, row);
    text_.setFillColor(sf::Color::Black);
}


void Button::setFillColor(const sf::Color& c)
{
    square_.setFillColor(c);
}

