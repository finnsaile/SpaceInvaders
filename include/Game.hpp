#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include "Player.hpp"
#include "State.hpp"
#include "Engine.hpp"
#include "Bullet.hpp"


class Game : public State {
public:
    //inherited functions
    virtual void init();
    virtual void cleanup();

    virtual void pause();
    virtual void resume();

    virtual void handleEvents();
    virtual void update();
    virtual void draw();
    
public:
    Game(Engine* app);

private:
    std::vector<std::unique_ptr<Bullet>> m_bullets;
    std::unique_ptr<Player> m_player;
    sf::Clock m_clock;

private:
    bool fire_bullet;
};