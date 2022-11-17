#pragma once
#include <SFML/Graphics.hpp>
#include "GameEntity.hpp"

/**
 * @brief Bullet object derived form DynamicGameEntity.
 * 
 */
class Bullet : public DynamicGameEntity {
public:
    /**
     * @brief Construct a new Bullet with position, velocity, scale and possibly texture path.
     * 
     * @param pos starting postion
     * @param vel velocity
     * @param scale scale passed down from engine
     * @param model possible texture path
     */
    Bullet(sf::Vector2f pos, float vel, const sf::Vector2f& scale, const std::string& model = "");
    virtual ~Bullet();
    /**
     * @brief Update position of bullet sprite.
     * 
     * @param frame_time time passed since last update
     * @param delta_time time step
     */
    virtual void update(float frame_time, float delta_time);

    /**
     * @brief Get the Global Bounds of the bullet sprite.
     * 
     * @return sf::FloatRect global bounds
     */
    virtual sf::FloatRect getGlobalBounds();
    /**
     * @brief Get the displayed position of the bullet sprite.
     * 
     * @return sf::Vector2f position
     */
    virtual sf::Vector2f getDisplayedPos();
private:
    /**
     * @brief Helper function to create bullet model.
     * 
     * @param model texture path of bullet. If empty, the default model will be used
     */
    void initBulletModel(const std::string& model);
    /**
     * @brief Calculate one movement step of the bullet based on delta time and velocity.
     * 
     * @param delta_time time step
     * @return sf::Vector2f movement vector
     */
    virtual sf::Vector2f calcMovementStep(const float delta_time);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; 
private:
    // sprite variables
    sf::Sprite m_bullet_sprite;
    sf::Texture m_bullet_texture;
};