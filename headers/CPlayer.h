#pragma once 
#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include <algorithm>

enum State {UP, DOWN, LEFT, RIGHT, UPRIGHT, UPLEFT, DOWNRIGHT, DOWNLEFT, REST};

class CPlayer : public sf::Drawable, public sf::Transformable
{
    public:
        CPlayer(sf::Vector2f& scaleVec);
        virtual ~CPlayer();
        void playerTick();
        void setState(bool W, bool A, bool S, bool D);

    private:
        double m_accumulator = 0;
        State m_state = REST;
        sf::Sprite m_player_sprite;
        sf::Texture m_player_texture;
        sf::Clock m_clock;
        sf::Vector2f& m_scale;
        std::vector<State> m_stack_x;
        std::vector<State> m_stack_y;

        void initPlayerModel();
        sf::Vector2f calcMovement(float delta_time);   
        void handleStateStack(bool& boolIn, std::vector<State>& vecIn, State stateIn);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

