#pragma once

#include <memory>

class Engine;

/**
 * @brief Represents a game state used by the engine.
 * 
 */
class State {
public:
    /**
     * @brief Construct a new State object.
     * 
     * @param app engine which the state belongs to
     */
    State(Engine* app);
    virtual ~State();
    virtual void init() = 0;
    virtual void cleanup() = 0;

    virtual void pause() = 0;
    virtual void resume() = 0;

    virtual void handleEvents() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;

    /**
     * @brief Call the change state function of the engine given a new state.
     * This will mark this state for deletion.
     * 
     * @param state new state
     */
    void changeState(std::unique_ptr<State> state);

    // pointer to owning engine
    Engine* const m_app;
};