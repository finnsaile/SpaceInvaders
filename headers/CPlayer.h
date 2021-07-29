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
        ~CPlayer();
        void playerTick();
        void setState(bool W, bool A, bool S, bool D);

    private:
        long long bigcounter = 0;
        long long bigc = 0;
        double m_accumulator = 0;
        State m_state = REST;
        sf::Sprite m_player_sprite;
        sf::Texture m_player_texture;
        sf::Clock m_clock;
        sf::Vector2f& m_scale;
        sf::Vector2f m_current_pos;
        sf::Vector2f m_previous_pos;
        std::vector<State> m_vecX;
        std::vector<State> m_vecY;

        void initPlayerModel();
        sf::Vector2f calcMovement(float delta_time);   
        void handleVector(bool& boolIn, std::vector<State>& vecIn, State stateIn);
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

