#pragma once
#include <SFML/Graphics.hpp>
#include "GameEntity.hpp"

/**
 * @brief Meteor game entity
 * 
 */
class Meteor : public DynamicGameEntity {
public:
    /**
     * @brief Construct a new Meteor.
     * 
     * @param hp hitpoints 
     * @param pos starting position 
     * @param vel velocity
     * @param scale scale passed down from engine
     */
    Meteor(size_t hp, sf::Vector2f pos, float vel, const sf::Vector2f& scale);
    virtual ~Meteor();
    /**
     * @brief Update position of meteor sprite based on passed time.
     * 
     * @param frame_time passed time since last update
     * @param delta_time delta time for time step
     */
    virtual void update(float frame_time, float delta_time);

    /**
     * @brief Get the Global Bounds of the meteor sprite.
     * 
     * @return sf::FloatRect spirte bounds 
     */
    virtual sf::FloatRect getGlobalBounds();
    /**
     * @brief Get the position of the meteor sprite.
     * 
     * @return sf::Vector2f sprite postion
     */
    virtual sf::Vector2f getDisplayedPos();

    /**
     * @brief Get current hp of meteor.
     * 
     * @return size_t hp
     */
    size_t getHp();
    /**
     * @brief Set the current hp of the meteor.
     * 
     * @param hp 
     */
    void setHp(size_t hp);
    /**
     * @brief Static function to clear all meteor textures if no more meteors exist.
     * 
     */
    static void clearMeteorTextures();
private:
    /**
     * @brief Helper function to create meteor model.
     * 
     */
    void initMeteorModel();
    /**
     * @brief Calculate one movement step of the meteor based on delta time and velocity.
     * 
     * @param delta_time time step
     * @return sf::Vector2f movement vector
     */
    virtual sf::Vector2f calcMovementStep(const float delta_time);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    sf::Sprite m_meteor_sprite;
    size_t m_hp;
    
    /**
     * @brief Static variables used to keep track of the total amount of meteors and
     * to store all meteor textures.
     * 
     */
    static std::vector<sf::Texture> m_meteor_textures;
    static size_t m_meteor_counter;
};