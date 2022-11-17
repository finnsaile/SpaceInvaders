#pragma once

#include <SFML/Graphics.hpp>

#include "State.hpp"

/**
 * @brief Tilescrenn state.
 * 
 */
class TitleScreen : public State {
public:
    /**
     * @brief Construct a new Title Screen object
     * 
     * @param app pointe to owning engine
     */
    TitleScreen(Engine* app);
public:
    /**
     * @brief Helper function to create title screen.
     * 
     */
    virtual void init();
    /**
     * @brief Event loop for title screen.
     * 
     */
    virtual void handleEvents();
    /**
     * @brief Draws all entities to engine window.
     * 
     */
    virtual void draw();

    // unused functions
    virtual void cleanup();
    virtual void pause();
    virtual void resume();
    virtual void update();

private:
    sf::Text m_title_text;
    sf::Font m_font;
};