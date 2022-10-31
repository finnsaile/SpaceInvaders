#include "State.hpp"
#include "Engine.hpp"

State::State(Engine* app) : m_app{app} {}

State::~State() {}

void State::changeState(Engine* app, std::unique_ptr<State> state) {
        app->changeState(std::move(state));
    }