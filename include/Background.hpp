#include "GameEntity.hpp"

class Background : public StaticGameEntity {
public:
    Background(sf::Vector2f pos, const sf::Vector2f& scaleVec, const sf::Vector2u& size, std::string texture_path);
    virtual ~Background();
    
    virtual sf::FloatRect getGlobalBounds();
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    sf::Sprite m_background_sprite;
    sf::Texture m_background_texture;
};