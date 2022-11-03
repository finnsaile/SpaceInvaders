#include <iostream>
#include <exception>
#include <algorithm>
#include <cmath>
#include "Player.hpp"

using sf::Vector2f;

Player::Player(sf::Vector2f pos, float vel, const Vector2f& scaleVec) :
DynamicGameEntity(pos, vel, scaleVec),
m_fire_bullet_left{0.1},
m_fire_bullet_right{0.1} {
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

std::pair<sf::Vector2f, sf::Vector2f> Player::getCanonPositions() {
    sf::Vector2f left(m_current_pos);
    sf::Vector2f right(m_current_pos);

    //fraction by which the canons are ofset from the center of the sprite
    constexpr float X_FRAC_FROM_CENTER = 1.f/5.f;
    constexpr float Y_FRAC_FROM_CENTER = 1.f/3.f;

    left.x -= m_player_size.x * X_FRAC_FROM_CENTER;
    left.y -= m_player_size.y * Y_FRAC_FROM_CENTER;

    right.x += m_player_size.x * X_FRAC_FROM_CENTER;
    right.y -= m_player_size.y * Y_FRAC_FROM_CENTER;

    return {left, right};
}

void Player::initPlayerModel() {
    m_player_texture.loadFromFile("resources/Spaceship_06_ORANGE.png");
    m_player_texture.setSmooth(true);

    m_player_sprite = initSprite(m_current_pos, 150, m_player_texture);
    m_player_size = {m_player_sprite.getGlobalBounds().width, m_player_sprite.getGlobalBounds().height};
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    //draw bounding box
    // sf::RectangleShape rect;
    // rect.setSize(Vector2f(m_player_sprite.getGlobalBounds().width,  m_player_sprite.getGlobalBounds().height));
    // rect.setOrigin(rect.getSize().x /2, rect.getSize().y /2);
    // rect.setPosition(m_player_sprite.getPosition());
    // rect.setFillColor(sf::Color::Green);
    // target.draw(rect);

    target.draw(m_player_sprite);
}