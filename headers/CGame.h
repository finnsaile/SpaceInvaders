#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "CPlayer.h"

class CGame
{
    public:
        CGame();
        void runGame();
    private:
        sf::ContextSettings m_settings;
        sf::Event m_event;
        sf::Vector2f m_scale;
        std::unique_ptr<sf::RenderWindow> m_window;
        std::unique_ptr<CPlayer> m_player;
};