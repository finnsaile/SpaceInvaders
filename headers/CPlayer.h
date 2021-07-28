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
        void playerTick();
        void setState(bool W, bool A, bool S, bool D);

    private:
        double m_accumulator;
        State m_state;
        sf::RectangleShape m_playerRect;
        sf::Clock m_clock;
        sf::Vector2f& m_scale;
        sf::Vector2f m_current_pos;
        sf::Vector2f m_previous_pos;
        std::vector<State> m_vecX;
        std::vector<State> m_vecY;

        sf::Vector2f calcMovement(sf::Vector2f pos, float delta_time);   
        void handleVector(bool& boolIn, std::vector<State>& vecIn, State stateIn);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

