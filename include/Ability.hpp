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

/**
 * @brief Ability used to create Bullets and fire them at a certain velocity.
 * 
 */
class FireBullet : public Ability {
public:
    /**
     * @brief Construct a new Fire Bullet object.
     * 
     * @param cooldown cooldown of the ability
     * @param texture_path path to texture for the bullet. If not sepcified, defaults to empty string
     */
    FireBullet(float cooldown, const std::string& texture_path = "");
    virtual ~FireBullet();
    /**
     * @brief Create a bullet given a velocity, position and scale.
     * 
     * @param pos starting position of bullet
     * @param vel velocity if bullet
     * @param scale scale of bullet passed down from engine
     * @return std::unique_ptr<Bullet> created bullet
     */
    virtual std::unique_ptr<Bullet> useAbility(sf::Vector2f pos, float vel, sf::Vector2f scale);
    /**
     * @brief Call the useAbility function.
     * 
     * @param pos starting position of bullet
     * @param vel velocity if bullet
     * @param scale scale of bullet passed down from engine
     * @return std::unique_ptr<Bullet> 
     */
    std::unique_ptr<Bullet> operator()(sf::Vector2f pos, float vel, sf::Vector2f scale);
    /**
     * @brief Cpdate the ability timer and set the usability accordingly.
     * 
     */
    virtual void updateAbility();
private:
    std::string m_texture_path;
};