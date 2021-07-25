#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class CGame
{
    public:
        CGame();
        void runGame();
    private:
        sf::ContextSettings m_settings;
        sf::Event m_event;
        std::unique_ptr<sf::RenderWindow> m_window;
};