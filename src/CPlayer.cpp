#include "../headers/CPlayer.h"
#include <iostream>

CPlayer::CPlayer(sf::Vector2f& scaleVec) : 
m_state(REST),
m_scale(scaleVec),
m_accumulator(0)
{
    m_playerRect.setSize(sf::Vector2f(49,49));
    m_playerRect.setFillColor(sf::Color::Green);
    m_playerRect.setOrigin(sf::Vector2f(25,25));
    m_playerRect.setPosition(300, 400);
    m_playerRect.setScale(m_scale);
    m_current_pos = m_playerRect.getPosition();    //m_vecX.reserve(2);
    //m_vecY.reserve(2);
}

void CPlayer::playerTick()
{
    float frame_time = m_clock.restart().asSeconds(), delta_time = 0.001;
    if(frame_time > 0.25)
        frame_time = 0.25;

    m_accumulator += frame_time;

    while(m_accumulator >= delta_time)
    {
        m_previous_pos = m_current_pos;
        m_current_pos = calcMovement(m_current_pos, delta_time);    
        m_accumulator -= delta_time;
       // std::cout << m_accumulator << std::endl;
    }
    //std::cout << std::endl;
    const double alpha = m_accumulator / delta_time;
    
    sf::Vector2f new_position(m_current_pos.x * alpha + m_previous_pos.x * (1.0 - alpha), m_current_pos.y * alpha + m_previous_pos.y * (1.0 - alpha));
    m_playerRect.setPosition(new_position);
}

void CPlayer::setState(bool W, bool A, bool S, bool D)
{
    handleVector(W, m_vecY, UP);
    handleVector(S, m_vecY, DOWN);
    handleVector(A, m_vecX, LEFT);
    handleVector(D, m_vecX, RIGHT);
   
    if(!m_vecY.empty())
    {
        if(*(m_vecY.end() - 1) == UP) {W = true; S = false;}
        else if(*(m_vecY.end() - 1) == DOWN) {W = false; S = true;} 
    }

    if(!m_vecX.empty())
    {    
        if(*(m_vecX.end() - 1) == LEFT) {A = true; D = false;}
        else if(*(m_vecX.end() - 1) == RIGHT) {A = false; D = true;} 
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

void CPlayer::handleVector(bool& boolIn, std::vector<State>& vecIn, State stateIn)
{
    if(boolIn && std::find(vecIn.begin(), vecIn.end(), stateIn) == vecIn.end()) 
        vecIn.push_back(stateIn);
    else if(!boolIn && std::find(vecIn.begin(), vecIn.end(), stateIn) != vecIn.end())
        vecIn.erase(std::find(vecIn.begin(), vecIn.end(), stateIn));
}

sf::Vector2f CPlayer::calcMovement(sf::Vector2f pos, float delta_time)
{
    float x = 0, y = 0, vel = 600;

    switch(m_state)
        {
            case UP: y = - vel * delta_time; break;
            case DOWN: y = vel * delta_time; break;
            case LEFT: x = - vel * delta_time; break;
            case RIGHT: x = vel * delta_time; break;
            case UPLEFT: x = y = - vel * delta_time / sqrt(2); break;
            case UPRIGHT: y = - vel * delta_time / sqrt(2); x = - y; break;
            case DOWNLEFT: x = - vel * delta_time / sqrt(2); y = - x; break;
            case DOWNRIGHT: x = y = vel * delta_time / sqrt(2); break;
            case REST: x = 0; y = 0; break;
            default: x = 0; y = 0; break;
        }
    pos.x += x;
    pos.y += y;
    return pos;
}
void CPlayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_playerRect);
}