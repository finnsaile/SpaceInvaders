#include <iostream>
#include <exception>
#include <algorithm>
#include <cmath>
#include "Player.hpp"

using sf::Vector2f;

Player::Player(const Vector2f& scaleVec) :
DynamicGameEntity({300, 400}, 600, scaleVec) {
    initPlayerModel();
}

Player::~Player()
{}

void Player::update(float frame_time, float delta_time) {
    m_player_sprite.setPosition(calcNextPos(frame_time, delta_time));
}

void Player::addPlayerState(const PlayerState& state) {
    //check if state already in stack, and add if not
    if(state == UP || state == DOWN) {
        auto i = std::find(m_stack_y.begin(), m_stack_y.end(), state);
        if(i == m_stack_y.end())
            m_stack_y.push_back(state);
    }

    if(state == LEFT || state == RIGHT) {
        auto i = std::find(m_stack_x.begin(), m_stack_x.end(), state);
        if(i == m_stack_x.end())
            m_stack_x.push_back(state);
    }
}

void Player::removePlayerState(const PlayerState& state) {
    //check if state already in stack, and remove if present
    if(state == UP || state == DOWN) {
        auto i = std::find(m_stack_y.begin(), m_stack_y.end(), state);
        if(i != m_stack_y.end())
            m_stack_y.erase(i);
    }

    if(state == LEFT || state == RIGHT) {
        auto i = std::find(m_stack_x.begin(), m_stack_x.end(), state);
        if(i != m_stack_x.end())
            m_stack_x.erase(i);
    }
}

Vector2f Player::calcMovementStep(const float delta_time) {
    float x = 0, y = 0;
    float move_const = m_velocity * delta_time;

    if(!m_stack_y.empty())
        switch(m_stack_y.back()) {
            case UP: y = -move_const; break;
            case DOWN: y = move_const; break;
            default: throw(std::invalid_argument("y stack contains unexpected value: " 
                        + std::to_string(m_stack_y.back()))); break;
        }

    if(!m_stack_x.empty())
        switch(m_stack_x.back()) {
            case LEFT: x = -move_const; break;
            case RIGHT: x = move_const; break;
            default: throw(std::invalid_argument("x stack contains unexpected value: " 
                            + std::to_string(m_stack_x.back()))); break;
        }

    //normalize diagonal movement speed
    if(x != 0 && y != 0) {
        y /= sqrt(2);
        x /= sqrt(2);
    }

    return {x, y};
}

void Player::initPlayerModel() {   
    const int final_size = 200;
    m_player_texture.loadFromFile("resources/player3.png");
    m_player_texture.setSmooth(true);

    Vector2f texture_size(m_player_texture.getSize());

    float fscale = m_scale.x * (final_size/texture_size.x) < m_scale.y * (final_size/texture_size.y) ?
                  m_scale.x * (final_size/texture_size.x) : m_scale.y * (final_size/texture_size.y);
    
    m_player_sprite.setTexture(m_player_texture);
    m_player_sprite.setOrigin(texture_size.x/2, texture_size.y/2);
    m_player_sprite.setScale(fscale, fscale);
    m_player_sprite.setPosition(300, 400);
    m_previous_pos = m_current_pos = m_player_sprite.getPosition();
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    //draw bounding box
    sf::RectangleShape rect;
    rect.setSize(Vector2f(m_player_sprite.getGlobalBounds().width,  m_player_sprite.getGlobalBounds().height));
    rect.setOrigin(rect.getSize().x /2, rect.getSize().y /2);
    rect.setPosition(m_player_sprite.getPosition());
    rect.setFillColor(sf::Color::Green);
    target.draw(rect);

    target.draw(m_player_sprite);
}