#include "Gui.hpp"

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
// , card_()
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

void Gui::drawScreen(void)
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

void Gui::setButtonColor(const GameUtils::ButtonLoc btn,  sf::Color c)
{
    buttons_[btn].setFillColor(c);
}

void Gui::setBannerText(const GameUtils::BannerLoc ban, const std::string& str)
{
    banners_[ban].setText(str);
}