#include <iostream>
#include <random>
#include "Game.hpp"
#include "TitleScreen.hpp"

using sf::Keyboard, sf::Event;
using sf::Vector2f;

Game::Game(Engine* app) : 
State(app),
m_meteor_timer{0},
m_background({0,0}, app->m_scale, app->m_window.getSize(), "resources/bg57.png"),
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

                    case Keyboard::Q:
                        fire_bomb = true;
                        break;

                    case Keyboard::M:
                        m_meteors.push_back(std::make_unique<Meteor>(1, sf::Vector2f(400, 0), 500, m_app->m_scale));
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
                    
                    case Keyboard::Q:
                        fire_bomb = false;
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

    if(fire_bomb) {
        sf::Vector2f sc = {m_app->m_scale.x * 1.5f, m_app->m_scale.y * 1.5f};
        std::unique_ptr<Bullet> bomb = m_player->m_fire_bomb(m_player->getDisplayedPos(), 1200, sc);
        if(bomb)
            m_bombs.push_back(std::move(bomb));
    }

    spawnMeteor(frame_time);

    //update position of both bullets and meteors
    for(auto& b : m_bullets)
        b->update(frame_time, delta_time);

    for(auto& b : m_bombs)
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
    
    //crosscheck bullets and meteors for collision
    m_bullets.erase(std::remove_if(m_bullets.begin(), m_bullets.end(), 
        [&](std::unique_ptr<Bullet>& b){
            bool hit = false;
            //remove meteors hit by the bullet
            m_meteors.erase(std::remove_if(m_meteors.begin(), m_meteors.end(),
                [&](std::unique_ptr<Meteor>& m){
                    if(m->getGlobalBounds().contains(b->getDisplayedPos())) {
                        hit = true;
                        size_t hp = m->getHp();
                        if(hp > 0)
                            m->setHp(hp - 1);
                        else
                            return true;
                    }
                    return false;
                }), m_meteors.end());
            
            return hit;
        }), m_bullets.end());

    m_bombs.erase(std::remove_if(m_bombs.begin(), m_bombs.end(),
        [&](std::unique_ptr<Bullet>& b){
            for(auto& m : m_meteors) {
                if(m->getGlobalBounds().contains(b->getDisplayedPos())) {
                    m_meteors.clear();
                    return true;
                }
            }
            return false;
        }), m_bombs.end());
}

void Game::spawnMeteor(float frame_time) {
    m_meteor_timer += frame_time;
    float level = 2;
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_real_distribution<float> dist_pos(0, m_app->m_window.getSize().x);
    //used to scale meteor velocity and size
    std::uniform_real_distribution<float> dist_scale(0.5, 1.5);
    std::uniform_int_distribution<size_t> dist_hp(1, 5);
    //spawn meteor if time has been reached
    if(m_meteor_timer > (1.f / level)) {
        m_meteor_timer = 0;
        m_meteors.push_back(std::make_unique<Meteor>(dist_hp(rng),
            sf::Vector2f(dist_pos(rng), -100.f), dist_scale(rng) * 300.f, dist_scale(rng) * m_app->m_scale));
    }
}

void Game::pause() {
    m_player->resetPlayerState();
}

void Game::draw() {
    m_app->m_window.draw(m_background);
    
    for(auto& b : m_bullets)
        m_app->m_window.draw(*b);
    
    for(auto& b : m_bombs)
        m_app->m_window.draw(*b);

    for(auto& m : m_meteors)
        m_app->m_window.draw(*m);

    m_app->m_window.draw(*m_player);
}

void Game::init() {}
void Game::cleanup() {}

void Game::resume() {}