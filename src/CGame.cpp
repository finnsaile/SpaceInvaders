#include "../headers/CGame.h"
#include <iostream>

CGame::CGame()
{
    m_settings.antialiasingLevel = 8;
    m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(600, 800),
                                                "Space Invaders", 
                                                sf::Style::Titlebar | sf::Style::Close, 
                                                m_settings);
    m_window->setFramerateLimit(150);
    m_window->setKeyRepeatEnabled(false);                                            
}

void CGame::runGame()
{
    bool W = false, A = false, S = false, D = false;
    while(m_window->isOpen())
    {
        while(m_window->pollEvent(m_event))
        {
            switch(m_event.type)
            {
                case sf::Event::Closed:
                    m_window->close();
                    break;
                
                case sf::Event::KeyPressed:
                    switch(m_event.key.code)
                    {
                        case sf::Keyboard::Escape:
                            m_window->close();
                            break;

                        case sf::Keyboard::W:
                            W = true;
                            break;

                        case sf::Keyboard::A:
                            A = true;
                            break;

                        case sf::Keyboard::S:
                            S = true;
                            break;

                        case sf::Keyboard::D:
                            D = true;
                            break;

                        default:
                            break;
                    }
                    break;

                case sf::Event::KeyReleased:
                    switch(m_event.key.code)
                    {
                        case sf::Keyboard::W:
                            W = false;
                            break;

                        case sf::Keyboard::A:
                            A = false;
                            break;

                        case sf::Keyboard::S:
                            S = false;
                            break;

                        case sf::Keyboard::D:
                            D = false;
                            break;

                        default:
                            break;
                    }
                    break;

                default:
                    break;
            }
        }
        m_player.setState(W, A, S, D);
        m_player.playerTick();
        m_window->clear(sf::Color::Transparent);
        m_window->draw(m_player);
        m_window->display();
    }
}