#include "Engine.hpp"
#include "Game.hpp"

using sf::Keyboard, sf::Event;
using sf::VideoMode, sf::Style::Titlebar, sf::Style::Close;
using sf::Vector2f;

using std::unique_ptr, std::make_unique;

Engine::Engine() {
    init();
    
    m_states.push_back(make_unique<Game>(this));
}

void Engine::init() {
    unsigned int height = VideoMode::getDesktopMode().height / 1.2;
    unsigned int width = VideoMode::getDesktopMode().width / 3;
    float uniform_scale = (height / 1200.f) < (width / 853.f) ? 
                            (height / 1200.f) : (width / 853.f);
    m_scale = Vector2f(uniform_scale, uniform_scale);

    m_settings.antialiasingLevel = 8;

    m_window.create({width, height}, "Space Invaders", Close, m_settings);
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
    if(!m_states.empty())
        m_states.pop_back();

    m_states.push_back(std::move(state));
}

void Engine::pushState(unique_ptr<State> state) {
    if(!m_states.empty())
        m_states.back()->pause();

    m_states.push_back(std::move(state));
}

void Engine::popState(unique_ptr<State> state) {
    if(!m_states.empty())
        m_states.pop_back();
    
    m_states.back()->resume();
}

void Engine::handleEvents() {
    m_states.back()->handleEvents(this);
}

void Engine::update() {
    m_states.back()->update(this);
}

void Engine::draw() {
    for(auto& s : m_states)
        s->draw(this);
}


