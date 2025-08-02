#include "Banner.hpp"

Banner::Banner()
{
}

Banner::~Banner()
{
}

Banner::Banner(const std::string& str
                , const sf::Font font
                , const int COL
                , const int ROW
                , const sf::Color color)
: handle_(str, font, TEXT_THICK)
{
    width_ = handle_.getLocalBounds().getSize().x;
    handle_.setPosition(COL - width_/2, ROW);
    handle_.setFillColor(color);
}

void Banner::setText(const std::string& str)
{
    handle_.setString(str);
}