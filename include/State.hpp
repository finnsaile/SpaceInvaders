#pragma once

#include <memory>

class Engine;

class State {
public:
    State(Engine* app);
    virtual ~State();
    virtual void init() = 0;
    virtual void cleanup() = 0;

    virtual void pause() = 0;
    virtual void resume() = 0;

    virtual void handleEvents() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;

    void changeState(std::unique_ptr<State> state);

    Engine* m_app;
};