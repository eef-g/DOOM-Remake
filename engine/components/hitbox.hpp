#ifndef CE_HITBOX_HPP
#define CE_HITBOX_HPP

#include <SFML/Graphics.hpp>
#include "ce_components.hpp"

namespace CE_Components {
    class Hitbox : public IComponent {
        private:
            // Variables
            sf::RectangleShape shape;
            sf::Vector2f size;
            sf::Vector2f offset;
            sf::Vector2f scale;
            sf::Vector2f position;
        public:
            // Constructor
            Hitbox(
                sf::RectangleShape shape,
                sf::Vector2f position,
                sf::Vector2f size,
                sf::Vector2f offset,
                sf::Vector2f scale, 
                bool debug=false
            );
            Hitbox(CE_Components::IComponent *sprite, float scale, float offset_x, float offset_y);
            Hitbox();
            // Destructor
            virtual ~Hitbox() override;

            // Functions
            void update(float frameTime) override;
            void render(sf::RenderTarget *target) override;
            std::string getType() override { return "Hitbox"; };
            bool intersects(Hitbox *other);

            // Getters
            sf::Vector2f getPosition() { return this->position; };
            sf::Vector2f getSize() {return this->size; };
            sf::Vector2f getOffset() { return this->offset; }

            // Setters
            void setPosition(sf::Vector2f position) { this->position = position; };
            void setSize(sf::Vector2f size) { this->size = size; };
            void setOffset(sf::Vector2f offset) {this->offset = offset; };
    };
}

#endif