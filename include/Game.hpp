#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include "Player.hpp"

class Game {
    public:
        Game();
        void runGame();
    private:
        sf::ContextSettings m_settings;
        sf::Event m_event;
        sf::Vector2f m_scale;
        sf::RenderWindow m_window;
        std::unique_ptr<Player> m_player;
};