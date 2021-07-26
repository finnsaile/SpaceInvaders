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
    std::cout << 1/m_clock.restart().asSeconds() << std::endl;
}

void CPlayer::setState(bool W, bool A, bool S, bool D)
{
    handleVector(W, m_vecY, UP);
    handleVector(S, m_vecY, DOWN);
    handleVector(A, m_vecX, LEFT);
    handleVector(D, m_vecX, RIGHT);

    // if(W && std::find(m_vecY.begin(), m_vecY.end(), UP) == m_vecY.end()) 
    //     m_vecY.push_back(UP);
    // else if(!W && std::find(m_vecY.begin(), m_vecY.end(), UP) != m_vecY.end())
    //     m_vecY.erase(std::find(m_vecY.begin(), m_vecY.end(), UP));

    // if(S && std::find(m_vecY.begin(), m_vecY.end(), DOWN) == m_vecY.end()) 
    //     m_vecY.push_back(DOWN);
    // else if(!S && std::find(m_vecY.begin(), m_vecY.end(), DOWN) != m_vecY.end())
    //     m_vecY.erase(std::find(m_vecY.begin(), m_vecY.end(), DOWN));
    
    // if(A && std::find(m_vecX.begin(), m_vecX.end(), LEFT) == m_vecX.end()) 
    //     m_vecX.push_back(LEFT);
    // else if(!A && std::find(m_vecX.begin(), m_vecX.end(), LEFT) != m_vecX.end())
    //     m_vecX.erase(std::find(m_vecX.begin(), m_vecX.end(), LEFT));

    // if(D && std::find(m_vecX.begin(), m_vecX.end(), RIGHT) == m_vecX.end()) 
    //     m_vecX.push_back(RIGHT);
    // else if(!D && std::find(m_vecX.begin(), m_vecX.end(), RIGHT) != m_vecX.end())
    //     m_vecX.erase(std::find(m_vecX.begin(), m_vecX.end(), RIGHT));
   
    if(!m_vecY.empty())
    {
        if(*(m_vecY.end() - 1) == UP) {W = true; S = false;}
        else if(*(m_vecY.end() - 1) == DOWN) {W = false; S = true;} 
    }
    if(m_vecY.size() == static_cast<size_t>(2))
        std::cout << "TRUE" << std::endl;
    if(!m_vecX.empty())
    {    
        if(*(m_vecX.end() - 1) == LEFT) {A = true; D = false;}
        else if(*(m_vecX.end() - 1) == RIGHT) {A = false; D = true;} 
    }
    if(m_vecX.size() == static_cast<size_t>(2))
        std::cout << "TRUE" << std::endl;

    // if(W && S)
    // {
    //     if(m_state == UP || m_state == UPRIGHT || m_state == UPLEFT)
    //         W = false;
    //     else 
    //         S = false;
    // }
    // if(A && D)
    // {
    //     if(m_state == LEFT || m_state == UPLEFT || m_state == DOWNLEFT)
    //         A = false;
    //     else 
    //         D = false;
    // }


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

void CPlayer::handleVector(bool& boolIn, std::vector<State>& vecIn, State stateIn)
{
    if(boolIn && std::find(vecIn.begin(), vecIn.end(), stateIn) == vecIn.end()) 
        vecIn.push_back(stateIn);
    else if(!boolIn && std::find(vecIn.begin(), vecIn.end(), stateIn) != vecIn.end())
        vecIn.erase(std::find(vecIn.begin(), vecIn.end(), stateIn));
}


void CPlayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_playerRect);
}