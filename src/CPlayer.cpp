#include "../headers/CPlayer.h"
#include <iostream>

CPlayer::CPlayer(sf::Vector2f& scaleVec) : 
m_scale(scaleVec)
{
    initPlayerModel();
}

CPlayer::~CPlayer()
{

}

void CPlayer::playerTick()
{
    int factor;
    float frame_time = m_clock.restart().asSeconds(), delta_time = 0.001;

    m_accumulator += frame_time;
    factor = static_cast<int>(m_accumulator / delta_time);
    m_accumulator -= factor * delta_time;

    m_player_sprite.move(calcMovement(factor * delta_time));   
}
    

void CPlayer::setState(bool W, bool A, bool S, bool D)
{
    handleStateStack(W, m_stack_y, UP);
    handleStateStack(S, m_stack_y, DOWN);
    handleStateStack(A, m_stack_x, LEFT);
    handleStateStack(D, m_stack_x, RIGHT);
   
    if(!m_stack_y.empty())
    {
        if(*(m_stack_y.end() - 1) == UP) {W = true; S = false;}
        else if(*(m_stack_y.end() - 1) == DOWN) {W = false; S = true;} 
    }

    if(!m_stack_x.empty())
    {    
        if(*(m_stack_x.end() - 1) == LEFT) {A = true; D = false;}
        else if(*(m_stack_x.end() - 1) == RIGHT) {A = false; D = true;} 
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

void CPlayer::handleStateStack(bool& dir_bool, std::vector<State>& stack, State state)
{
    if(dir_bool && std::find(stack.begin(), stack.end(), state) == stack.end()) 
        stack.push_back(state);
    else if(!dir_bool && std::find(stack.begin(), stack.end(), state) != stack.end())
        stack.erase(std::find(stack.begin(), stack.end(), state));
}

sf::Vector2f CPlayer::calcMovement(float delta_time)
{
    float x = 0, y = 0, vel = 600;
    float move_const = vel * delta_time;
     switch(m_state)
        {
            case UP: y = - move_const; break;
            case DOWN: y = move_const; break;
            case LEFT: x = - move_const; break;
            case RIGHT: x = move_const; break;
            case UPLEFT: x = y = - move_const / sqrt(2); break;
            case UPRIGHT: y = - move_const / sqrt(2); x = - y; break;
            case DOWNLEFT: x = - move_const / sqrt(2); y = - x; break;
            case DOWNRIGHT: x = y = move_const / sqrt(2); break;
            case REST: x = 0; y = 0; break;
            default: x = 0; y = 0; break;
        }

    return sf::Vector2f(x, y);
}

void CPlayer::initPlayerModel()
{   
    int final_size = 200;
    m_player_texture.loadFromFile("resources/player3.png");
    m_player_texture.setSmooth(true);
    float texture_size_x = m_player_texture.getSize().x;
    float texture_size_y = m_player_texture.getSize().y;

    float fscale = m_scale.x * (final_size/texture_size_x) < m_scale.y * (final_size/texture_size_y) ?
                  m_scale.x * (final_size/texture_size_x) : m_scale.y * (final_size/texture_size_y);
    
    std::cout << fscale << std::endl;
    m_player_sprite.setTexture(m_player_texture);
    m_player_sprite.setOrigin(texture_size_x/2, texture_size_y/2);
    m_player_sprite.setScale(fscale, fscale);
    m_player_sprite.setPosition(300, 400);
}

void CPlayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::RectangleShape rect;
    rect.setSize(sf::Vector2f(m_player_sprite.getLocalBounds().width,  m_player_sprite.getLocalBounds().height));
    rect.setOrigin(rect.getSize().x /2, rect.getSize().y /2);
    rect.setPosition(m_player_sprite.getPosition());
    rect.setFillColor(sf::Color::Green);
    //target.draw(rect);
    target.draw(m_player_sprite);
}