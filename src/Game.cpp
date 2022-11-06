#include <iostream>
#include <random>
#include "Game.hpp"
#include "TitleScreen.hpp"

using sf::Keyboard, sf::Event;
using sf::Vector2f;

Game::Game(Engine* app) : 
State(app),
m_meteor_timer{0},
fire_bullet{false} {
    sf::Vector2u win_size = m_app->m_window.getSize();
    m_player = std::make_unique<Player>(sf::Vector2f(win_size.x/2.f, win_size.y/2.f),
                                         800, m_app->m_scale);                         
}

Game::~Game() {
    Meteor::clearMeteorTextures();
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

                    case Keyboard::M:
                        m_meteors.push_back(std::make_unique<Meteor>(sf::Vector2f(400, 0), 500, m_app->m_scale));
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

    //create left and right bullet
    if(fire_bullet) {
        auto canon_pos = m_player->getCanonPositions();
        std::unique_ptr<Bullet> bullet_l = m_player->m_fire_bullet_left(canon_pos.first, 1000, m_app->m_scale);
        std::unique_ptr<Bullet> bullet_r = m_player->m_fire_bullet_right(canon_pos.second, 1000, m_app->m_scale);
        if(bullet_l)
            m_bullets.push_back(std::move(bullet_l));
        if(bullet_r)
            m_bullets.push_back(std::move(bullet_r));
    }

    spawnMeteor(frame_time);

    //update position of both bullets and meteors
    for(auto& b : m_bullets)
        b->update(frame_time, delta_time);

    for(auto& m : m_meteors)
        m->update(frame_time, delta_time);
    
    sf::Vector2f window_size = m_app->m_window.getView().getSize();
    sf::FloatRect window_rect({0, 0}, window_size);
    
    //remove bullets that left the upper screen
    m_bullets.erase(std::remove_if(m_bullets.begin(), m_bullets.end(),
        [&](std::unique_ptr<Bullet>& b){
            return (b->getGlobalBounds().top + b->getGlobalBounds().height) < 0;}), m_bullets.end());
    
    //remove meteors that left the lower screen
    m_meteors.erase(std::remove_if(m_meteors.begin(), m_meteors.end(),
        [&](std::unique_ptr<Meteor>& m){return (m->getGlobalBounds().top > window_size.y);}), m_meteors.end());
    
    auto& meteors = m_meteors;
    //crosscheck bullets and meteors for collision
    m_bullets.erase(std::remove_if(m_bullets.begin(), m_bullets.end(), 
        [&](std::unique_ptr<Bullet>& b){
            size_t size = meteors.size();
            //remove meteors hit by the bullet
            m_meteors.erase(std::remove_if(m_meteors.begin(), m_meteors.end(),
                [&](std::unique_ptr<Meteor>& m){return (m->getGlobalBounds().contains(b->getDisplayedPos()));}), m_meteors.end());
            //check if elements were removed
            if(meteors.size() < size)
                return true;
            
            return false;
        }), m_bullets.end());

}

void Game::spawnMeteor(float frame_time) {
    m_meteor_timer += frame_time;
    float level = 4;
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_real_distribution<float> dist_pos(0, m_app->m_window.getSize().x);
    //used to scale meteor velocity and size
    std::uniform_real_distribution<float> dist_scale(0.5, 1.5);
    
    //spawn meteor if time has been reached
    if(m_meteor_timer > (1.f / level)) {
        m_meteor_timer = 0;
        m_meteors.push_back(std::make_unique<Meteor>(
            sf::Vector2f(dist_pos(rng), -100.f), dist_scale(rng) * 300.f, dist_scale(rng) * m_app->m_scale));
    }
}

void Game::pause() {
    m_player->resetPlayerState();
}

void Game::draw() {
    for(auto& b : m_bullets)
        m_app->m_window.draw(*b);
    
    for(auto& m : m_meteors)
        m_app->m_window.draw(*m);

    m_app->m_window.draw(*m_player);
}

void Game::init() {}
void Game::cleanup() {}

void Game::resume() {}