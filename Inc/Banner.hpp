#pragma once
#include <SFML/Graphics.hpp>

class Banner
{
    private:
        sf::Text handle_;
        int width_;

        const int TEXT_THICK = 40;

    public:
        Banner();
        ~Banner();

        Banner(const std::string& str
            , const sf::Font& font
            , const int COL
            , const int ROW
            , const sf::Color color);

    void setText(const std::string& str);   
    const sf::Text& getHandle(void) const { return handle_; }

};