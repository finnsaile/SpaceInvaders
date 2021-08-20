#include "../headers/CGame.h"
#include <iostream>

CGame::CGame()
{
    unsigned int height = sf::VideoMode::getDesktopMode().height / 1.2;
    unsigned int width = sf::VideoMode::getDesktopMode().width / 3;
    float uniform_scale = (height / static_cast<float>(1200)) < (width / static_cast<float>(853)) ? 
                            (height / static_cast<float>(1200)) : (width / static_cast<float>(853));
    m_scale = sf::Vector2f(uniform_scale, uniform_scale);

    std::cout << m_scale.x << std::endl;
    std::cout << m_scale.y << std::endl;
    m_settings.antialiasingLevel = 8;
    m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(width, height),
                                                "Space Invaders", 
                                                sf::Style::Titlebar | sf::Style::Close, 
                                                m_settings);
    m_player = std::make_unique<CPlayer>(m_scale);
    m_window->setFramerateLimit(144);
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
        m_player->setState(W, A, S, D);
        m_player->playerTick();
        m_window->clear(sf::Color::Transparent);
        m_window->draw(*m_player);
        m_window->display();
    }
}