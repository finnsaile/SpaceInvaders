#pragma once

#include <vector>
#include <State.hpp>
#include <SFML/Graphics.hpp>

class State;

class Engine {
public:
    Engine();

    void changeState(std::unique_ptr<State> state);
    void pushState(std::unique_ptr<State> state);
    void popState(std::unique_ptr<State> state);

    void handleEvents();
    void update();
    void draw();

    void run();
public:
    sf::RenderWindow m_window;
    sf::Vector2f m_scale;
    
private:
    std::vector<std::unique_ptr<State>> m_states;

    sf::ContextSettings m_settings;

private:
    void init();
};