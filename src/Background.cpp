#include "Background.hpp"

Background::Background(sf::Vector2f pos, const sf::Vector2f& scaleVec, const sf::Vector2u& size, std::string texture_path) :
StaticGameEntity(pos, scaleVec) {
    m_background_texture.loadFromFile(texture_path);
    m_background_texture.setRepeated(true);
    m_background_texture.setSmooth(true);
    m_background_sprite.setTexture(m_background_texture);
    m_background_sprite.setScale(m_scale);
    m_background_sprite.setTextureRect(sf::IntRect(0, 0, size.x, size.y));
    m_background_sprite.setPosition(m_pos);
}

Background::~Background() {}

sf::FloatRect Background::getGlobalBounds() {
    return m_background_sprite.getGlobalBounds();
}

void Background::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_background_sprite);
}