#pragma once 
#include <SFML/Graphics.hpp>
#include <vector>

#include "GameEntity.hpp"


enum PlayerState {UP, DOWN, LEFT, RIGHT};

class Player : public DynamicGameEntity {
public:
    Player(const sf::Vector2f& scaleVec);
    virtual ~Player();
    virtual void update(float frame_time, float delta_time);

    void addPlayerState(const PlayerState&);
    void removePlayerState(const PlayerState&);

private:
    //player model
    sf::Sprite m_player_sprite;
    sf::Texture m_player_texture;

    //input handling
    std::vector<PlayerState> m_stack_x;
    std::vector<PlayerState> m_stack_y;

private:
    void initPlayerModel();
    sf::Vector2f calcMovementStep(const float delta_time);   
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

