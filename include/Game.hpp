#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

#include "Player.hpp"
#include "State.hpp"
#include "Engine.hpp"
#include "Bullet.hpp"
#include "Meteor.hpp"
#include "Background.hpp"

/**
 * @brief Game state.
 * 
 */
class Game : public State {
public:
    /**
     * @brief Construct a new Game passing a pointer to the owning engine.
     * 
     * @param app owning engine
     */
    Game(Engine* app);
    virtual ~Game();
public:
    // unused functions
    virtual void init();
    virtual void cleanup();
    virtual void resume();

    /**
     * @brief Call resetPlayerStates function from player to prevent inputs
     * being stuck after resuming.
     * 
     */
    virtual void pause();

    /**
     * @brief Handle user input.
     * 
     */
    virtual void handleEvents();
    /**
     * @brief Update all entities that are part of the game.
     * Calculating the frame time, first advance the player.
     * Then create new bullets if the abilties are being used and call spawnMeteor.
     * Afterwards, advance bullets and meteors and then check for collisions and
     * entities leaving the screen.
     */
    virtual void update();
    /**
     * @brief Draw all game entities in the correct order.
     * 
     */
    virtual void draw();

private:
    // vectors holding game entities
    std::vector<std::unique_ptr<Bullet>> m_bullets;
    std::vector<std::unique_ptr<Bullet>> m_bombs;
    std::vector<std::unique_ptr<Meteor>> m_meteors;
    // player pointer
    std::unique_ptr<Player> m_player;
    // clock used to measure frame time
    sf::Clock m_clock;
    // timer used to measure time since last meteor spawn
    float m_meteor_timer;
    // game background
    Background m_background;
    
private:
    // bools used to register ability usage
    bool m_fire_bullet;
    bool m_fire_bomb;
private:
    /**
     * @brief Helper function to spwan new meteor.
     * Checks if timer has reched threshold and calculates 
     * random position, scale and velocity of new meteor before adding it 
     * to the vector.
     * 
     * @param frame_time 
     */
    void spawnMeteor(float frame_time);
};