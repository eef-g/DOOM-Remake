#ifndef CE_SPRITE_HPP
#define CE_SPRITE_HPP
#include <SFML/Graphics.hpp>
#include <string>
#include "ce_components.hpp"
namespace CE_Components {
    class Sprite : public IComponent {
        public:
            // Variables
            sf::Sprite sprite;
            sf::Texture texture;
            sf::Vector2f position;
            sf::Vector2f scale;
            sf::Vector2f offset;
            sf::Vector2f size;

            // Constructor
            Sprite(
                sf::Sprite sprite,
                sf::Texture texture,
                sf::Vector2f position,
                sf::Vector2f scale,
                sf::Vector2f offset,
                sf::Vector2f size
            );
            Sprite(
                std::string texturePath,
                sf::Vector2f imageSize
            );
            Sprite(
                sf::Texture textureObject,
                sf::Vector2f spriteSize
            );
            Sprite() {};

            // Destructor
            virtual ~Sprite() override {};

            // Functions
            void update(float frameTime) override;
            void render(sf::RenderTarget *target) override;
            std::string getType() override { return "Sprite"; };

            // Getters
            sf::Vector2f getPosition() { return this->position; };
            sf::Vector2f getScale() { return this->scale; };
            sf::Vector2f getOffset() { return this->offset; };
            sf::Vector2f getSize() { return this->size; };
            sf::Texture* getTexture() { return &this->texture; };
            sf::Sprite* getSprite() { return &this->sprite; };


            // Setters
            void setPosition(sf::Vector2f position) { this->position = position; };
            void setScale(sf::Vector2f scale) { this->scale = scale; };
            void setOffset(sf::Vector2f offset) { this->offset = offset; };
            void setSize(sf::Vector2f size) { this->size = size; };
            void setTexture(sf::Texture texture) { this->texture = texture; };
            void setSprite(sf::Sprite sprite) { this->sprite = sprite; };
    };
}

#endif