#pragma once

#include <vector>
#include <State.hpp>
#include <SFML/Graphics.hpp>
#include <utility>

//struct used to mark states on the stack that are 
//to be deleted after tick occured
struct StatePair {
    std::unique_ptr<State> state;
    bool delete_bool;
};


class State;

class Engine {
public:
    Engine();

    void changeState(std::unique_ptr<State> state);
    void pushState(std::unique_ptr<State> state);
    void popState();

    void handleEvents();
    void update();
    void draw();

    void run();
public:
    sf::RenderWindow m_window;
    sf::Vector2f m_scale;
    
private:
    std::vector<StatePair> m_states;
    sf::ContextSettings m_settings;

private:
    void init();
};