#include "GameEntity.hpp"
#include <iostream>

using sf::Vector2f;
using sf::Sprite, sf::Texture;

GameEntity::GameEntity(const Vector2f& scale) : 
m_scale{scale} {}

GameEntity::~GameEntity() {}

DynamicGameEntity::DynamicGameEntity(Vector2f pos, float vel, const Vector2f& scale) :
GameEntity(scale),
m_velocity{vel * scale.x},
m_accumulator{0},
m_current_pos{pos},
m_previous_pos{pos} {}

DynamicGameEntity::~DynamicGameEntity() {}

Vector2f DynamicGameEntity::calcNextPos(float frame_time, float delta_time) {
    m_accumulator += frame_time;

    if(m_accumulator > 0.1) {
        m_accumulator = 0.1;
    }

    while(m_accumulator >= delta_time) {
        m_previous_pos = m_current_pos;
        m_current_pos += calcMovementStep(delta_time);
        m_accumulator -= delta_time;
    }

    const float alpha = m_accumulator / delta_time;
    
    Vector2f temp_pos = (alpha * m_current_pos) + m_previous_pos * (1.f - alpha);
    return temp_pos;
}

Sprite GameEntity::initSprite(Vector2f pos, const float final_width, Texture& texture) {
    Sprite temp_sprite;

    texture.setSmooth(true);

    Vector2f texture_size(texture.getSize());

    float fscale = m_scale.x * (final_width/texture_size.x);


    temp_sprite.setTexture(texture);
    temp_sprite.setOrigin(texture_size.x/2, texture_size.y/2);
    temp_sprite.setScale(fscale, fscale);
    temp_sprite.setPosition(pos);

    return temp_sprite;
}

Vector2f DynamicGameEntity::getPos() {
    return m_current_pos;
}

float DynamicGameEntity::getVel() {
    return m_velocity;
}

StaticGameEntity::StaticGameEntity(Vector2f pos, const Vector2f& scale) :
GameEntity(scale),
m_pos{pos} {}

StaticGameEntity::~StaticGameEntity() {}

Vector2f StaticGameEntity::getPos() {
    return m_pos;
}