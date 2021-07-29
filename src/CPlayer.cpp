#include "../headers/CPlayer.h"
#include <iostream>

CPlayer::CPlayer(sf::Vector2f& scaleVec) : 
m_scale(scaleVec)
{
    initPlayerModel();
}


CPlayer::~CPlayer()
{
    std::cout << "[" << bigcounter/static_cast<double>(bigc) << "]" << std::endl;
}
void CPlayer::playerTick()
{
    float frame_time = m_clock.restart().asSeconds(), delta_time = 0.001;
    int counter = 0;
    m_accumulator += frame_time;

    while(m_accumulator >= delta_time)
    {  
        counter += 1;
        m_accumulator -= delta_time;
        m_player_sprite.move(calcMovement(delta_time));     
    }
    bigcounter += counter;
    bigc += 1;
    if(counter >= 18)
    std::cout << counter << std::endl;
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

sf::Vector2f CPlayer::calcMovement(float delta_time)
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

    return sf::Vector2f(x, y);
}

void CPlayer::initPlayerModel()
{   
    int final_size = 200;
    m_player_texture.loadFromFile("resources/player3.png");
    m_player_texture.setSmooth(false);
    float texture_size_x = m_player_texture.getSize().x;
    float texture_size_y = m_player_texture.getSize().y;

    float fscale = m_scale.x * (final_size/texture_size_x) < m_scale.y * (final_size/texture_size_y) ?
                  m_scale.x * (final_size/texture_size_x) : m_scale.y * (final_size/texture_size_y);
    
    std::cout << fscale << std::endl;
    m_player_sprite.setTexture(m_player_texture);
    m_player_sprite.setOrigin(texture_size_x/2, texture_size_y);
    m_player_sprite.setScale(fscale, fscale);
    m_player_sprite.setPosition(300, 400);
}

void CPlayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_player_sprite);
}