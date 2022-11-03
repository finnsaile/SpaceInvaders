#include <iostream>
#include "Game.hpp"
#include "TitleScreen.hpp"

using sf::Keyboard, sf::Event;
using sf::Vector2f;

Game::Game(Engine* app) : 
State(app),
fire_bullet{false} {
    sf::Vector2u win_size = m_app->m_window.getSize();
    m_player = std::make_unique<Player>(sf::Vector2f(win_size.x/2.f, win_size.y/2.f),
                                         600, m_app->m_scale);                         
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

                    case Keyboard::C:
                        changeState(std::make_unique<TitleScreen>(m_app));
                        break;

                    case Keyboard::V:
                        m_app->pushState(std::make_unique<TitleScreen>(m_app));
                        break;

                    case Keyboard::B:
                        m_app->popState();
                        break;

                    case Keyboard::Space:
                            fire_bullet = true;
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
                    case Keyboard::Space:
                            fire_bullet = false;
                        break;

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
    float frame_time = m_clock.restart().asSeconds(), delta_time = 0.01;
    m_player->update(frame_time, delta_time);

    if(fire_bullet) {
        auto canon_pos = m_player->getCanonPositions();
        std::unique_ptr<Bullet> bullet_l = m_player->m_fire_bullet_left(canon_pos.first, 1200, m_app->m_scale);
        std::unique_ptr<Bullet> bullet_r = m_player->m_fire_bullet_right(canon_pos.second, 1200, m_app->m_scale);
        if(bullet_l)
            m_bullets.push_back(std::move(bullet_l));
        if(bullet_r)
            m_bullets.push_back(std::move(bullet_r));
    }

    for(auto& b : m_bullets)
        b->update(frame_time, delta_time);

    sf::Vector2f window_size = m_app->m_window.getView().getSize();
    sf::FloatRect window_rect({0, 0}, window_size);
    
    m_bullets.erase(std::remove_if(m_bullets.begin(), m_bullets.end(),
        [&](std::unique_ptr<Bullet>& b){return !(b->getGlobalBounds().intersects(window_rect));}), m_bullets.end());
}

void Game::draw() {
    for(auto& b : m_bullets)
        m_app->m_window.draw(*b);
    m_app->m_window.draw(*m_player);
}

void Game::init() {}
void Game::cleanup() {}
void Game::pause() {}
void Game::resume() {}