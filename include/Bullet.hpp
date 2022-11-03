#pragma once
#include <SFML/Graphics.hpp>
#include "GameEntity.hpp"

class Bullet : public DynamicGameEntity {
public:
    Bullet(sf::Vector2f pos, float vel, const sf::Vector2f& scaleVec);
    virtual ~Bullet();
    virtual void update(float frame_time, float delta_time);

    virtual sf::FloatRect getGlobalBounds();
    virtual sf::Vector2f getDisplayedPos();
private:
    void initBulletModel();
    virtual sf::Vector2f calcMovementStep(const float delta_time);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const; 
private:
    sf::Sprite m_bullet_sprite;
    sf::Texture m_bullet_texture;
};