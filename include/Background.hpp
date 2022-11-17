#include "GameEntity.hpp"

/**
 * @brief Background for game and menu derived from StaticGameEntity.
 * 
 */
class Background : public StaticGameEntity {
public:
    /**
     * @brief Construct a new Background given a position, size and texture.
     * 
     * @param pos position of the background
     * @param scale scale passed down from engine
     * @param size final size of background
     * @param texture_path path to background texture
     */
    Background(sf::Vector2f pos, const sf::Vector2f& scale, const sf::Vector2u& size, std::string texture_path);
    virtual ~Background();
    
    /**
     * @brief Get the global bounds of the background sprite.
     * 
     * @return sf::FloatRect global bounds
     */
    virtual sf::FloatRect getGlobalBounds();
private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
    // sprite variables
    sf::Sprite m_background_sprite;
    sf::Texture m_background_texture;
};