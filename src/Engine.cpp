#include "Engine.hpp"
#include "Game.hpp"
#include "TitleScreen.hpp"
#include <iostream>
#include <exception>


constexpr float Y_SCREEN_FACTOR = 5.f/6.f;
constexpr float WINDOWRATIO = 4.f/3.f;

using sf::Keyboard, sf::Event;
using sf::VideoMode, sf::Style::Titlebar, sf::Style::Close;
using sf::Vector2f;

using std::unique_ptr, std::make_unique;

Engine::Engine() {
    init();
    pushState(make_unique<TitleScreen>(this));
}

void Engine::init() {
    unsigned int height = VideoMode::getDesktopMode().height;

    //determine by which factor objects need to be scaled where standart values are 2560x1440
    float uniform_scale = (height / 1440.f);

    m_scale = Vector2f(uniform_scale, uniform_scale);

    m_settings.antialiasingLevel = 8;

    //make window size a fraction of the screen size
    unsigned int window_height = height * Y_SCREEN_FACTOR; 
    unsigned int window_width = window_height / WINDOWRATIO;
    m_window.create({window_width, window_height}, "Space Invaders", Close, m_settings);
    m_window.setFramerateLimit(200);
    m_window.setKeyRepeatEnabled(false);
}

void Engine::run() {
    while(m_window.isOpen()) {
        handleEvents();
        update();
        draw();
    }
}

void Engine::changeState(unique_ptr<State> state) {
    popState();

    pushState(std::move(state));
}

void Engine::pushState(unique_ptr<State> state) {
    m_states.push_back({std::move(state), false});
}

void Engine::popState() {
    for (std::vector<StatePair>::reverse_iterator i = m_states.rbegin(); 
        i != m_states.rend(); ++i ) {
        if(!i->delete_bool) {
            i->delete_bool = true;
            break;
        }
    }
}

void Engine::handleEvents() {
    if(m_states.empty())
        throw(std::runtime_error("No states in engine stack when trying to handle events!"));

    m_states.back().state->handleEvents();

    m_states.erase(std::remove_if(m_states.begin(), m_states.end(),
        [](StatePair& s){return s.delete_bool;}), m_states.end());
}

void Engine::update() {
    if(m_states.empty())
        throw(std::runtime_error("No states in engine stack when trying to update state!"));
    
    m_states.back().state->update();
}

void Engine::draw() {
    m_window.clear(sf::Color::Transparent);
    for(auto& s : m_states)
        s.state->draw();
    m_window.display();
}


