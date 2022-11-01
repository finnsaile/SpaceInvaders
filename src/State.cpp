#include "State.hpp"
#include "Engine.hpp"

State::State(Engine* app) : m_app{app} {}

State::~State() {}

void State::changeState(std::unique_ptr<State> state) {
        m_app->changeState(std::move(state));
    }