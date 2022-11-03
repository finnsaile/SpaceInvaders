#include "Ability.hpp"

Ability::Ability(float cooldwon) :
m_cooldown{cooldwon},
m_usable{true} {}

Ability::~Ability() {}

FireBullet::FireBullet(float cooldown) :
Ability(cooldown) {}

FireBullet::~FireBullet() {}


std::unique_ptr<Bullet> FireBullet::useAbility(sf::Vector2f pos, float vel, sf::Vector2f scale) {
    updateAbility();
    if(!m_usable)
        return nullptr;

    m_ability_timer.restart();
    m_usable = false;

    return std::make_unique<Bullet>(pos, vel, scale);
}

std::unique_ptr<Bullet> FireBullet::operator()(sf::Vector2f pos, float vel, sf::Vector2f scale) {
    return useAbility(pos, vel, scale);
}

void FireBullet::updateAbility() {
    if(m_usable)
        return;
    
    if(m_ability_timer.getElapsedTime().asSeconds() > m_cooldown)
        m_usable = true;
}