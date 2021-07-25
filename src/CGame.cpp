#include "../headers/CGame.h"

CGame::CGame()
{
    m_settings.antialiasingLevel = 8;
    m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(600, 800),
                                                "Space Invaders", 
                                                sf::Style::Titlebar | sf::Style::Close, 
                                                m_settings);
    m_window->setFramerateLimit(150);                                            
}

void CGame::runGame()
{
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

                        default:
                            break;
                    }
                default:
                    break;
            }
        }

        m_window->clear(sf::Color::Yellow);
        m_window->display();
    }
}