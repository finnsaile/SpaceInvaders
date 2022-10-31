#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include "Player.hpp"
#include "State.hpp"
#include "Engine.hpp"


class Game : public State {
public:
    virtual void init();
    virtual void cleanup();

    virtual void pause();
    virtual void resume();

    virtual void handleEvents(Engine* app);
    virtual void update(Engine* app);
    virtual void draw(Engine* app);
    
public:
    Game(Engine* app);

private:
    sf::Event m_event;
    std::unique_ptr<Player> m_player;
};