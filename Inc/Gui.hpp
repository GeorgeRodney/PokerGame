#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include "Banner.hpp"
#include "GameUtils.hpp"
#include "CardSprite.hpp"

class Gui 
{
    private:
        std::vector<Button> buttons_;
        std::vector<Banner> banners_;
        sf::Font font_; 
        std::vector<CardSprite> cards_;
        sf::Event event_;
        sf::RenderWindow window_;


    public:
        Gui();
        ~Gui();
        Gui(const sf::VideoMode& mode
            , const std::string& gameName
            , const std::string& fontFile);

        const sf::Font& getFont(void) const { return font_; }
        const sf::Event& getEvent(void) const { return event_; }
        const sf::RectangleShape& getButtonBound(const GameUtils::ButtonLoc btn) const { return buttons_[btn].getRect(); }
        int getButtonSize(void) const { return buttons_.size(); }
        const sf::Text& getBanner(const GameUtils::BannerLoc ban) const { return banners_[ban].getHandle(); }
        const bool isWindowOpen(void) const { return window_.isOpen(); }
        bool pollEvent(sf::Event& event) { return window_.pollEvent(event); }
        const sf::RenderWindow& getWindow(void) { return window_; }
    
        bool pollEvent(void);   
        void closeWindow(void);
        void clearWindow(void);
        void drawScreen(const bool firstGo);
        void display(void);
        void debugButtons(void);

        void addBanner(Banner b);
        void addButton(Button btn);
        void addCard(CardSprite c);

        void setButtonColor(const GameUtils::ButtonLoc btn, const sf::Color c);
        void setBannerText(const GameUtils::BannerLoc ban, const std::string& str);
        void setCard(const GameUtils::CardLoc card, const std::string& imgFile);

        void drawBanner(sf::RenderWindow* window, GameUtils::BannerLoc ban);

};