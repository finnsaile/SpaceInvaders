#pragma once 
#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include <algorithm>

enum State {UP, DOWN, LEFT, RIGHT, UPRIGHT, UPLEFT, DOWNRIGHT, DOWNLEFT, REST};

class CPlayer : public sf::Drawable, public sf::Transformable
{
    public:
        CPlayer();
        void playerTick();
        void setState(bool W, bool A, bool S, bool D);

    private:
        State m_state;
        sf::RectangleShape m_playerRect;
        sf::Clock m_clock;

        std::vector<State> m_vecX;
        std::vector<State> m_vecY;

        void handleVector(bool& boolIn, std::vector<State>& vecIn, State stateIn);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

