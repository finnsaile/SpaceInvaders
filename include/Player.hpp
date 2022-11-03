#pragma once 
#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>

#include "GameEntity.hpp"
#include "Ability.hpp"

enum PlayerState {UP, DOWN, LEFT, RIGHT};

class Player : public DynamicGameEntity {
public:
    Player(sf::Vector2f pos, float vel, const sf::Vector2f& scaleVec);
    virtual ~Player();
    virtual void update(float frame_time, float delta_time);

    void addPlayerState(const PlayerState&);
    void removePlayerState(const PlayerState&);

    std::pair<sf::Vector2f, sf::Vector2f> getCanonPositions();
    virtual sf::Vector2f getDisplayedPos();
    virtual sf::FloatRect getGlobalBounds();
public:
    FireBullet m_fire_bullet_left;
    FireBullet m_fire_bullet_right;
private:
    void initPlayerModel();
    virtual sf::Vector2f calcMovementStep(const float delta_time);   
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    //player model
    sf::Sprite m_player_sprite;
    sf::Texture m_player_texture;
    sf::Vector2f m_player_size;

    //input handling
    std::vector<PlayerState> m_stack_x;
    std::vector<PlayerState> m_stack_y;
};

