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
, banner_()
, window_(mode, gameName)
, font_()
// , card_()
{
    font_.loadFromFile(fontFile);
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
}

void Gui::addBanner(Banner b)
{
    banner_.push_back(b);
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
    banner_[ban].setText(str);
}