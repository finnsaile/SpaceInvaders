#pragma once 
#include <SFML/Graphics.hpp>

/**
 * @brief Base class for all game enities
 * 
 */
class GameEntity : public sf::Drawable {
public:
    /**
     * @brief Construct a new Game Entity object.
     * 
     * @param scale scale of the object passed down from game engine
     */
    GameEntity(const sf::Vector2f& scale);
    virtual ~GameEntity() = 0;

protected:
    /**
     * @brief Helper function to used to create sprite with correct scale and smoothness
     * sets origin of the sprite to its center.
     * 
     * @param pos initial position of the sprite
     * @param final_width desired width of sprite before global scaling is applied
     * @param texture reference to sprite texture
     * @return sf::Sprite initialized sprite
     */
    sf::Sprite initSprite(sf::Vector2f pos, const float final_width, sf::Texture& texture);
    // Reference to globally used engine scale
    const sf::Vector2f& m_scale;
};

/**
 * @brief Derived class from GameEntity used to create dynamic entities that can move.
 * 
 */
class DynamicGameEntity : public GameEntity {
public:
    /**
     * @brief Construct a new Dynamic Game Entity object.
     * 
     * @param pos initial positioin
     * @param vel velocity
     * @param scale scale passed down from game engine
     */
    DynamicGameEntity(sf::Vector2f pos, float vel, const sf::Vector2f& scale);
    virtual ~DynamicGameEntity() = 0;
    /**
     * @brief Calculate the next displayed position of the object using time steps and interpolation.
     * The returned value is not the actual position of the object but the interpolated position used
     * to draw the sprite.
     * 
     * @param frame_time time since last update
     * @param delta_time delta time step
     * @return sf::Vector2f next position of of sprite 
     */
    virtual sf::Vector2f calcNextPos(float frame_time, float delta_time);

    virtual sf::Vector2f getDisplayedPos() = 0;
    virtual sf::FloatRect getGlobalBounds() = 0;
    /**
     * @brief Get the current acctual positon of the object.
     * 
     * @return sf::Vector2f acctual position
     */
    sf::Vector2f getPos();
    /**
     * @brief Get the velocity.
     * 
     * @return float velocity
     */
    float getVel();
    
protected:
    //for movement calculation
    float m_velocity;
    float m_accumulator;
    sf::Vector2f m_current_pos;
    sf::Vector2f m_previous_pos;

protected: 
    virtual sf::Vector2f calcMovementStep(float delta_time) = 0;
};

/**
 * @brief Derived class from GameEntity used to create static, non moving entities.
 * 
 */
class StaticGameEntity : public GameEntity {
public: 
    /**
     * @brief Construct a new Static Game Entity.
     * 
     * @param pos position of entity
     * @param scale scale passed down from game engine
     */
    StaticGameEntity(sf::Vector2f pos, const sf::Vector2f& scale);
    virtual ~StaticGameEntity() = 0;
    virtual sf::FloatRect getGlobalBounds() = 0;

    /**
     * @brief Get the positon of entity.
     * 
     * @return sf::Vector2f position
     */
    sf::Vector2f getPos();
protected:
    sf::Vector2f m_pos;
};