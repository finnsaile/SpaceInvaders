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

    virtual void handleEvents(Engine* app) = 0;
    virtual void update(Engine* app) = 0;
    virtual void draw(Engine* app) = 0;

    void changeState(Engine* app, std::unique_ptr<State> state);

    Engine* m_app;
};