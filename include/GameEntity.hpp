#pragma once 
#include <SFML/Graphics.hpp>

class GameEntity : public sf::Drawable {
public:
    GameEntity(const sf::Vector2f& scale);
    virtual ~GameEntity() = 0;

protected:
    sf::Sprite initSprite(sf::Vector2f pos, const float final_width, sf::Texture& texture);
    const sf::Vector2f& m_scale;
};

class DynamicGameEntity : public GameEntity {
public:
    DynamicGameEntity(sf::Vector2f pos, float vel, const sf::Vector2f& scale);
    virtual ~DynamicGameEntity() = 0;
    virtual sf::Vector2f calcNextPos(float frame_time, float delta_time);

    virtual sf::Vector2f getDisplayedPos() = 0;
    virtual sf::FloatRect getGlobalBounds() = 0;
    sf::Vector2f getPos();
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

class StaticGameEntity : public GameEntity {
public: 
    StaticGameEntity(sf::Vector2f pos, const sf::Vector2f& scale);
    virtual ~StaticGameEntity() = 0;
    virtual sf::FloatRect getGlobalBounds() = 0;

    sf::Vector2f getPos();
protected:
    sf::Vector2f m_pos;

protected:
    sf::Sprite initSprite(sf::Vector2f pos, const float final_width, sf::Texture& texture);
};