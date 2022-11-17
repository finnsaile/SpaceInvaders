#pragma once

#include <vector>
#include <State.hpp>
#include <SFML/Graphics.hpp>
#include <utility>

/**
 * @brief struct used to store states and a boolean,
 * used to mark them for deletion if necessary.
 * 
 */
struct StatePair {
    std::unique_ptr<State> state;
    bool delete_bool;
};


class State;

/**
 * @brief Main engine class that contains the main loop and window.
 * 
 */
class Engine {
public:
    /**
     * @brief Construct a new Engine.
     * 
     */
    Engine();

    /**
     * @brief Add a new state to the state stack and mark the topmost 
     * unmarked state for deletion.
     * 
     * @param state new state
     */
    void changeState(std::unique_ptr<State> state);
    /**
     * @brief Push a new state onto the state stack.
     * 
     * @param state new state
     */
    void pushState(std::unique_ptr<State> state);
    /**
     * @brief Mark the topmost unmarked state for deletion.
     * 
     */
    void popState();

    /**
     * @brief Main engine loop handling events, updating states and drawing to the window.
     * 
     */
    void run();
public:
    // window variables
    sf::RenderWindow m_window;
    sf::Vector2f m_scale;
    sf::ContextSettings m_settings;
    
private:
    // state stack
    std::vector<StatePair> m_states;

private:
    /**
     * @brief Helper function to initialize the window and calculate the correct scale.
     * 
     */
    void init();

    /**
     * @brief Call the handleEvents function of the current state and
     * delete all marked states afterwards.
     * 
     */
    void handleEvents();

    /**
     * @brief Call the update function of the current state.
     * 
     */
    void update();

    /**
     * @brief Clear the window, call the draw function of every state and
     * display the window.
     * 
     */
    void draw();
};