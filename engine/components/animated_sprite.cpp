#include "animated_sprite.hpp"

namespace CE_Components {
    AnimatedSprite::AnimatedSprite() {
        // Animated Sprite specific variables
        this->animFrames = 0;
        this->animTimer = 0.f;
        this->frameTime = 0.f;
        CE_Components::Sprite();
    }

    AnimatedSprite::AnimatedSprite(
        std::string spritesheetPath,
        int rowCount,
        int colCount
    ) {
        // Animated Sprite specific variables
        this->animFrames = 0;
        this->animTimer = 0.f;
        this->frameTime = 0.f;

        // Sprite specific variables
        sf::Texture texture;
        texture.loadFromFile(spritesheetPath);
        sf::Vector2f imageSize = sf::Vector2f(texture.getSize().x / colCount, texture.getSize().y / rowCount);
        CE_Components::Sprite(
            texture,
            imageSize
        );
    }
}