#include "Meteor.hpp"
#include <filesystem>
#include <random>
#include <iostream>

namespace fs = std::filesystem;

std::vector<sf::Texture> Meteor::m_meteor_textures;
size_t Meteor::m_meteor_counter = 0;

void Meteor::clearMeteorTextures() {
    if(m_meteor_counter == 0) {
        std::vector<sf::Texture> temp;
        m_meteor_textures.swap(temp);
    }
}

Meteor::Meteor(size_t hp, sf::Vector2f pos, float vel, const sf::Vector2f& scaleVec) :
DynamicGameEntity(pos, vel, scaleVec),
m_hp{hp} {
    if(m_meteor_counter == 0) {
        std::vector<std::string> files;
        //find all meteor textures and load them into memory
        for(const auto& f : fs::directory_iterator("resources/meteors")) {
            sf::Texture temp_text;
            temp_text.loadFromFile(f.path());
            temp_text.setSmooth(true);
            m_meteor_textures.push_back(temp_text);
        }
    }
    m_meteor_counter++;
    initMeteorModel();
}

Meteor::~Meteor() {
    m_meteor_counter--;
}

void Meteor::update(float frame_time, float delta_time) {
    m_meteor_sprite.setPosition(calcNextPos(frame_time, delta_time));
}

sf::FloatRect Meteor::getGlobalBounds() {
    return m_meteor_sprite.getGlobalBounds();
}

sf::Vector2f Meteor::getDisplayedPos() {
    return m_meteor_sprite.getPosition();
}

void Meteor::initMeteorModel() {
    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_int_distribution<int> dist(0, m_meteor_textures.size() - 1);

    m_meteor_sprite = initSprite(m_current_pos, 100.f, m_meteor_textures[dist(rng)]);
}

sf::Vector2f Meteor::calcMovementStep(const float delta_time) {
    return {0, m_velocity * delta_time};
}

size_t Meteor::getHp() {
    return m_hp;
}

void Meteor::setHp(size_t hp) {
    m_hp = hp;
}

void Meteor::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(m_meteor_sprite);
}