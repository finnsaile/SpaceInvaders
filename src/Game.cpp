#include <iostream>
#include "Game.hpp"
#include "TitleScreen.hpp"

using sf::Keyboard, sf::Event;
using sf::Vector2f;

Game::Game(Engine* app) : 
State(app) {
    m_player = std::make_unique<Player>(m_app->m_scale);                                       
}

void Game::handleEvents() {
    sf::Event event;
    while(m_app->m_window.pollEvent(event))
    {
        switch(event.type)
        {
            case Event::Closed:
                m_app->m_window.close();
                break;
            
            case Event::KeyPressed:
                switch(event.key.code)
                {
                    case Keyboard::Escape:
                        m_app->m_window.close();
                        break;

                    case Keyboard::L:
                        changeState(std::make_unique<TitleScreen>(m_app));
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
                switch(event.key.code)
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

void Game::update() {
    m_player->playerTick();
}

void Game::draw() {
    m_app->m_window.draw(*m_player);
}

void Game::init() {}
void Game::cleanup() {}
void Game::pause() {}
void Game::resume() {}