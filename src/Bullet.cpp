#include "Bullet.hpp"
#include <iostream>

Bullet::Bullet(sf::Vector2f pos, float vel, const sf::Vector2f& scaleVec, const std::string& model) :
DynamicGameEntity(pos, vel, scaleVec) {
    initBulletModel(model);
}

Bullet::~Bullet() {}

void Bullet::update(float frame_time, float delta_time) {
    m_bullet_sprite.setPosition(calcNextPos(frame_time, delta_time));
}

sf::Vector2f Bullet::calcMovementStep(const float delta_time) {
    return {0, -delta_time * m_velocity};
}

void Bullet::initBulletModel(const std::string& model) {
    if(model.empty())
        m_bullet_texture.loadFromFile("resources/Bullet_Long_Orange.png");
    else
        m_bullet_texture.loadFromFile(model);
    m_bullet_texture.setSmooth(true);

    m_bullet_sprite = initSprite(m_current_pos, 60, m_bullet_texture);
}

sf::FloatRect Bullet::getGlobalBounds() {
    return m_bullet_sprite.getGlobalBounds();
}

sf::Vector2f Bullet::getDisplayedPos() {
    return m_bullet_sprite.getPosition();
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_bullet_sprite);
}
