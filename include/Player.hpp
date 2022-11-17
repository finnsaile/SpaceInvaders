#pragma once 
#include <SFML/Graphics.hpp>
#include <vector>
#include <utility>

#include "GameEntity.hpp"
#include "Ability.hpp"

/**
 * @brief Used to determine the direction the player is moving
 * 
 */
enum PlayerState {UP, DOWN, LEFT, RIGHT};

/**
 * @brief Controllable Player object
 * 
 */
class Player : public DynamicGameEntity {
public:
    /**
     * @brief Construct a new Player object
     * 
     * @param pos starting position of player
     * @param vel velocity of player
     * @param scale scale passed down from engine
     */
    Player(sf::Vector2f pos, float vel, const sf::Vector2f& scale);
    virtual ~Player();
    /**
     * @brief Update the position of the player sprite
     * 
     * @param frame_time time passed since last frame
     * @param delta_time time intervals used to calculate movement
     */
    virtual void update(float frame_time, float delta_time);

    /**
     * @brief Removes a PlayeStatea to the state stacks
     * 
     * @param state state that is added to the stack
     */
    void addPlayerState(const PlayerState& state);
    /**
     * @brief Removes a PlayeStatea to the state stacks
     * 
     * @param state state that is removed from the stack
     */
    void removePlayerState(const PlayerState& state);
    /**
     * @brief Clears both state stacks 
     * 
     */
    void resetPlayerState();

    /**
     * @brief Calculates the postion of the playermodel canons 
     * depending on player scale and position
     * 
     * @return std::pair<sf::Vector2f, sf::Vector2f> pair containing coordinates of left and right cannon
     */
    std::pair<sf::Vector2f, sf::Vector2f> getCanonPositions();
    /**
     * @brief Get the position of the player sprite
     * 
     * @return sf::Vector2f sprite position
     */
    virtual sf::Vector2f getDisplayedPos();
    /**
     * @brief Get the global bounds of the player sprite
     * 
     * @return sf::FloatRect global bounds
     */
    virtual sf::FloatRect getGlobalBounds();
public:
    // player abilities
    FireBullet m_fire_bullet_left;
    FireBullet m_fire_bullet_right;

    FireBullet m_fire_bomb;
private:
    /**
     * @brief Helper function to initialize the player model.
     * 
     */
    void initPlayerModel();
    /**
     * @brief Calculate the movement of the player sprite using the state stacks,
     * delta time and velocity of the player.
     * 
     * @param delta_time amount of time for which movement is calculated
     * @return sf::Vector2f movement vector
     */
    virtual sf::Vector2f calcMovementStep(const float delta_time);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    // player model values  
    sf::Sprite m_player_sprite;
    sf::Texture m_player_texture;
    sf::Vector2f m_player_size;

    // state stack for horizontal and vetical input
    std::vector<PlayerState> m_stack_x;
    std::vector<PlayerState> m_stack_y;
};

