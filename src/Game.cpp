#include <iostream>
#include "Game.hpp"

using sf::Keyboard, sf::Event;
using sf::VideoMode, sf::Style::Titlebar, sf::Style::Close;
using sf::Vector2f;

Game::Game(Engine* app) : 
State(app) {
    m_player = std::make_unique<Player>(app->m_scale);                                       
}

void Game::handleEvents(Engine* app) {
    while(app->m_window.pollEvent(m_event))
    {
        switch(m_event.type)
        {
            case Event::Closed:
                app->m_window.close();
                break;
            
            case Event::KeyPressed:
                switch(m_event.key.code)
                {
                    case Keyboard::Escape:
                        app->m_window.close();
                        break;

                    case Keyboard::W:
                        m_player->addPlayerState(UP);
                        break;

                    case Keyboard::A:
                        m_player->addPlayerState(LEFT);
                        break;

                    case Keyboard::S:
                        m_player->addPlayerState(DOWN);
                        break;

                    case Keyboard::D:
                        m_player->addPlayerState(RIGHT);
                        break;

                    default:
                        break;
                }
                break;

            case Event::KeyReleased:
                switch(m_event.key.code)
                {
                    case Keyboard::W:
                        m_player->removePlayerState(UP);
                        break;

                    case Keyboard::A:
                        m_player->removePlayerState(LEFT);
                        break;

                    case Keyboard::S:
                        m_player->removePlayerState(DOWN);
                        break;

                    case Keyboard::D:
                        m_player->removePlayerState(RIGHT);
                        break;

                    default:
                        break;
                }
                break;

            default:
                break;
        }
    }
}

void Game::update(Engine* app) {
    m_player->playerTick();
}

void Game::draw(Engine* app) {
    app->m_window.clear(sf::Color::Transparent);
    app->m_window.draw(*m_player);
    app->m_window.display();
}

void Game::init() {}
void Game::cleanup() {}
void Game::pause() {}
void Game::resume() {}