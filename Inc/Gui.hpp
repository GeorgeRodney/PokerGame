#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include "Banner.hpp"
#include "GameUtils.hpp"

class Gui 
{
    private:
        std::vector<Button> buttons_;
        std::vector<Banner> banner_;
        sf::RenderWindow window_;   
        sf::Font font_; 
        // std::vector<CardSprite> card_;
        sf::Event event_;


    public:
        Gui();
        ~Gui();
        Gui(const sf::VideoMode& mode
            , const std::string& gameName
            , const std::string& fontFile);

        const sf::Font& getFont(void) const { return font_; } 
        const sf::RenderWindow& getWindow(void) const { return window_; }
        const sf::Event& getEvent(void) const { return event_; }
        const sf::RectangleShape& getButtonBound(const GameUtils::ButtonLoc btn) const { return buttons_[btn].getRect(); }

        bool pollEvent(void);
        void closeWindow(void);
        void clearWindow(void);
        void drawScreen(void);

        void addBanner(Banner b);
        void addButton(Button btn);

        void setButtonColor(const GameUtils::ButtonLoc btn, const sf::Color c);
        void setBannerText(const GameUtils::BannerLoc ban, const std::string& str);

};