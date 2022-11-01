#include "TitleScreen.hpp"
#include "Engine.hpp"
#include "Game.hpp"

using sf::Keyboard, sf::Event;

TitleScreen::TitleScreen(Engine* app) : 
State(app) {
    init();
}

void TitleScreen::init() {
    m_font.loadFromFile("resources/OCRAEXT.TTF");
    m_title_text.setCharacterSize(80);
    m_title_text.setFillColor(sf::Color::Green);
    m_title_text.setString("Space Invaders");
    m_title_text.setFont(m_font);

    sf::FloatRect text_bounds = m_title_text.getLocalBounds();
    m_title_text.setOrigin(text_bounds.left + text_bounds.width/2, text_bounds.top + text_bounds.height/2);
    sf::Vector2u pos = m_app->m_window.getSize();
    m_title_text.setPosition(pos.x/2, pos.y/3);
}

void TitleScreen::handleEvents() {
    sf::Event event;
    while(m_app->m_window.pollEvent(event))
    {
        switch(event.type)
        {
            case Event::Closed:
                m_app->m_window.close();
                break;
            
            case Event::KeyPressed:
                changeState(std::make_unique<Game>(m_app));
                break;

            default:
                break;
        }
    }
}

void TitleScreen::draw() {
    m_app->m_window.draw(m_title_text);
}

void TitleScreen::update() {}

void TitleScreen::cleanup() {}
void TitleScreen::pause() {}
void TitleScreen::resume() {}