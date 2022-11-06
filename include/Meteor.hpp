#pragma once
#include <SFML/Graphics.hpp>
#include "GameEntity.hpp"

class Meteor : public DynamicGameEntity {
public:
    Meteor(sf::Vector2f pos, float vel, const sf::Vector2f& scaleVec);
    virtual ~Meteor();
    virtual void update(float frame_time, float delta_time);

    virtual sf::FloatRect getGlobalBounds();
    virtual sf::Vector2f getDisplayedPos();

    static void clearMeteorTextures();
private:
    void initMeteorModel();
    virtual sf::Vector2f calcMovementStep(const float delta_time);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
    sf::Sprite m_meteor_sprite;
    sf::Texture m_meteor_texture;

    static std::vector<sf::Texture> m_meteor_textures;
    static size_t m_meteor_counter;
};