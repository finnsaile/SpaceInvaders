#include "GameEntity.hpp"

using sf::Vector2f;

GameEntity::GameEntity(const Vector2f& scale) : 
m_scale{scale} {}

GameEntity::~GameEntity() {}

DynamicGameEntity::DynamicGameEntity(Vector2f pos, float vel, const Vector2f& scale) :
GameEntity(scale),
m_velocity{vel},
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