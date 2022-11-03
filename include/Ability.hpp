#pragma once

#include <SFML/Graphics.hpp>
#include "Bullet.hpp"

class Ability {
public:
    Ability(float cooldown);
    virtual ~Ability() = 0;
    virtual void updateAbility() = 0;

protected:
    sf::Clock m_ability_timer;
    float m_cooldown;
    bool m_usable;
};

class FireBullet : public Ability {
public:
    FireBullet(float cooldown);
    virtual ~FireBullet();
    std::unique_ptr<Bullet> useAbility(sf::Vector2f pos, float vel, sf::Vector2f scale);
    std::unique_ptr<Bullet> operator()(sf::Vector2f pos, float vel, sf::Vector2f scale);
    virtual void updateAbility();
};