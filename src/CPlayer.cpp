#include "../headers/CPlayer.h"
#include <iostream>

CPlayer::CPlayer() : 
m_state(REST)
{
    m_playerRect.setSize(sf::Vector2f(49,49));
    m_playerRect.setFillColor(sf::Color::Green);
    m_playerRect.setOrigin(sf::Vector2f(25,25));
    m_playerRect.setPosition(300, 400);
}

void CPlayer::playerTick()
{
    float x = 0, y = 0, vel = 600;
    switch(m_state)
    {
        case UP: y = - vel * m_clock.getElapsedTime().asSeconds(); break;
        case DOWN: y = vel * m_clock.getElapsedTime().asSeconds(); break;
        case LEFT: x = - vel * m_clock.getElapsedTime().asSeconds(); break;
        case RIGHT: x = vel * m_clock.getElapsedTime().asSeconds(); break;
        case UPLEFT: x = y = - vel * m_clock.getElapsedTime().asSeconds() / sqrt(2); break;
        case UPRIGHT: y = - vel * m_clock.getElapsedTime().asSeconds() / sqrt(2); x = - y; break;
        case DOWNLEFT: x = - vel * m_clock.getElapsedTime().asSeconds() / sqrt(2); y = - x; break;
        case DOWNRIGHT: x = y = vel * m_clock.getElapsedTime().asSeconds() / sqrt(2); break;
        case REST: x = 0; y = 0; break;
        default: x = 0; y = 0; break;
    }
    m_playerRect.move(x, y);
    m_clock.restart();
    std::cout << "X: " << m_playerRect.getPosition().x << ", Y: " << m_playerRect.getPosition().y << std::endl;
}

void CPlayer::setState(bool& W, bool& A, bool& S, bool& D)
{
    if(W && S)
    {
        if(m_state == UP || m_state == UPRIGHT || m_state == UPLEFT)
            W = false;
        else 
            S = false;
    }
    if(A && D)
    {
        if(m_state == LEFT || m_state == UPLEFT || m_state == DOWNLEFT)
            A = false;
        else 
            D = false;
    }


    if(W && !A && !S && !D) m_state = UP;
    else if(!W && !A && S && !D) m_state = DOWN;
    else if(!W && A && !S && !D) m_state = LEFT;
    else if(!W && !A && !S && D) m_state = RIGHT;
    else if(W && A && !S && !D) m_state = UPLEFT;
    else if(W && !A && !S && D) m_state = UPRIGHT;
    else if(!W && A && S && !D) m_state = DOWNLEFT;
    else if(!W && !A && S && D) m_state = DOWNRIGHT;
    else m_state = REST;
}

void CPlayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_playerRect);
}