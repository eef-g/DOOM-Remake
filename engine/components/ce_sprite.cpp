#include "ce_sprite.hpp"

namespace CE_Components {
    Sprite::Sprite(
        sf::Sprite sprite, 
        sf::Texture texture, 
        sf::Vector2f position, 
        sf::Vector2f scale, 
        sf::Vector2f offset, 
        sf::Vector2f size
    ) {
        this->sprite = sprite;
        this->texture = texture;
        this->position = position;
        this->scale = scale;
        this->offset = offset;
        this->size = size;
    }

    Sprite::Sprite(
        std::string texturePath, 
        sf::Vector2f imageSize
    ) {
        this->texture.loadFromFile(texturePath);
        this->sprite.setTexture(this->texture);
        this->sprite.setTextureRect(sf::IntRect(0, 0, imageSize.x, imageSize.y));
        this->sprite.setOrigin(imageSize.x / 2, imageSize.y / 2);
        this->position = sf::Vector2f(0.0f, 0.0f);
        this->scale = sf::Vector2f(1.0f, 1.0f);
        this->offset = sf::Vector2f(0.0f, 0.0f);
        this->size = sf::Vector2f(imageSize.x, imageSize.y);
    }

    void Sprite::update(float frameTime) {
        this->sprite.setPosition(this->position);
        this->sprite.setScale(this->scale);
        this->sprite.setTextureRect(sf::IntRect(0, 0, this->size.x, this->size.y));
    }

    void Sprite::render(sf::RenderTarget *target) {
        this->sprite.setPosition(this->position);
        this->sprite.setScale(this->scale);
        this->sprite.setTextureRect(sf::IntRect(0, 0, this->size.x, this->size.y));
        target->draw(this->sprite);
    }
}