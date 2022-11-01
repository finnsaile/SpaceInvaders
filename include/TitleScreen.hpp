#pragma once

#include <SFML/Graphics.hpp>

#include "State.hpp"

class TitleScreen : public State {
public:

    TitleScreen(Engine* app);
public:
    virtual void init();
    virtual void cleanup();

    virtual void pause();
    virtual void resume();

    virtual void handleEvents();
    virtual void update();
    virtual void draw();

private:
    sf::Text m_title_text;
    sf::Font m_font;
};