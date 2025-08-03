#include "Gui.hpp"
#include <iostream>

Gui::Gui()
{
}

Gui::~Gui()
{
}

Gui::Gui(const sf::VideoMode& mode
            , const std::string& gameName
            , const std::string& fontFile)
: buttons_()
, banners_()
, font_()
, cards_()
, window_(mode, gameName)
{
    if(!font_.loadFromFile(fontFile))
    {
        throw std::runtime_error("Gui.cpp failed to load font file.");
    }
}

bool Gui::pollEvent(void)
{
    return window_.pollEvent(event_);
}

void Gui::closeWindow(void)
{
    window_.close();
}

void Gui::clearWindow(void)
{
    window_.clear(sf::Color::White);
}

void Gui::drawScreen(const bool firstGo)
{
    // Buttons
    for (int j = 0; j < buttons_.size(); ++j)
    {
        window_.draw(buttons_[j].getRect());
        window_.draw(buttons_[j].getText());
    }
    // Banners
    for (int j = 0; j < banners_.size(); ++j)
    {
        window_.draw(banners_[j].getHandle());
    }
    // Cards
    if (!firstGo)
    {
        for (int j = 0; j < cards_.size(); ++j)
        {
            window_.draw(cards_[j].getSprite());
        }
    }
}

void Gui::debugButtons(void)
{
    for (int j = 0; j < buttons_.size(); ++j)
    {
        const sf::RectangleShape& r = buttons_[j].getRect();
        std::cout << "Button " << j
              << " Pos: (" << r.getPosition().x << "," << r.getPosition().y << ") "
              << "Size: (" << r.getSize().x << "," << r.getSize().y << ") "
              << "Color: (" << (int)r.getFillColor().r << ","
                           << (int)r.getFillColor().g << ","
                           << (int)r.getFillColor().b << ","
                           << (int)r.getFillColor().a << ")"
              << std::endl;
    }
}

void Gui::display(void)
{
    window_.display();
}

void Gui::addBanner(Banner b)
{
    banners_.push_back(b);
}

void Gui::addButton(Button btn)
{
    buttons_.push_back(btn);
}

void Gui::addCard(CardSprite c)
{
    cards_.push_back(c);
}

void Gui::setButtonColor(const GameUtils::ButtonLoc btn,  sf::Color c)
{
    buttons_[btn].setFillColor(c);
}

void Gui::setBannerText(const GameUtils::BannerLoc ban, const std::string& str)
{
    banners_[ban].setText(str);
}

void Gui::setCard(const GameUtils::CardLoc card, const std::string& imgFile)
{
    cards_[card].loadCardImage(imgFile);
}