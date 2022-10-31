#include <iostream>
#include "Game.hpp"

using sf::Keyboard, sf::Event;
using sf::VideoMode, sf::Style::Titlebar, sf::Style::Close;
using sf::Vector2f;

Game::Game() :
m_window() {
    unsigned int height = VideoMode::getDesktopMode().height / 1.2;
    unsigned int width = VideoMode::getDesktopMode().width / 3;
    float uniform_scale = (height / 1200.f) < (width / 853.f) ? 
                            (height / 1200.f) : (width / 853.f);
    m_scale = Vector2f(uniform_scale, uniform_scale);

    m_settings.antialiasingLevel = 8;

    m_window.create({width, height}, "Space Invaders", Close, m_settings);
    m_window.setFramerateLimit(200);
    m_window.setKeyRepeatEnabled(false);
    
    m_player = std::make_unique<Player>(m_scale);                                       
}

void Game::runGame() {
    while(m_window.isOpen())
    {
        while(m_window.pollEvent(m_event))
        {
            switch(m_event.type)
            {
                case Event::Closed:
                    m_window.close();
                    break;
                
                case Event::KeyPressed:
                    switch(m_event.key.code)
                    {
                        case Keyboard::Escape:
                            m_window.close();
                            break;

                        case Keyboard::W:
                            m_player->addState(UP);
                            break;

                        case Keyboard::A:
                            m_player->addState(LEFT);
                            break;

                        case Keyboard::S:
                            m_player->addState(DOWN);
                            break;

                        case Keyboard::D:
                            m_player->addState(RIGHT);
                            break;

                        default:
                            break;
                    }
                    break;

                case Event::KeyReleased:
                    switch(m_event.key.code)
                    {
                        case Keyboard::W:
                            m_player->removeState(UP);
                            break;

                        case Keyboard::A:
                            m_player->removeState(LEFT);
                            break;

                        case Keyboard::S:
                            m_player->removeState(DOWN);
                            break;

                        case Keyboard::D:
                            m_player->removeState(RIGHT);
                            break;

                        default:
                            break;
                    }
                    break;

                default:
                    break;
            }
        }

        m_player->playerTick();
        m_window.clear(sf::Color::Transparent);
        m_window.draw(*m_player);
        m_window.display();
    }
}