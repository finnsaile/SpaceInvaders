#pragma once 
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <algorithm>

enum State {UP, DOWN, LEFT, RIGHT};

class Player : public sf::Drawable, public sf::Transformable {
    public:
        Player(sf::Vector2f& scaleVec);
        virtual ~Player();
        void playerTick();

        void addState(const State&);
        void removeState(const State&);

    private:
        //for movement calculation
        float m_accumulator = 0;
        sf::Vector2f m_current_pos;
        sf::Vector2f m_previous_pos;
        sf::Clock m_clock;

        //player model
        sf::Sprite m_player_sprite;
        sf::Texture m_player_texture;
        sf::Vector2f& m_scale;

        //input handling
        std::vector<State> m_stack_x;
        std::vector<State> m_stack_y;

    private:
        void initPlayerModel();
        sf::Vector2f calcMovement(float delta_time);   
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

