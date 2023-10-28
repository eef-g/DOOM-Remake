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
            // TODO: Make this constructor more friendly to use (You can figure it out, idc)
            // Constructor
            Hitbox(
                sf::RectangleShape shape,
                sf::Vector2f position,
                sf::Vector2f size,
                sf::Vector2f offset,
                sf::Vector2f scale, 
                bool debug=false
            );
            Hitbox();
            // Destructor
            virtual ~Hitbox() override;

            // Functions
            void update(float frameTime) override;
            void render(sf::RenderTarget *target) override;
            bool intersects(Hitbox *other);

            // Getters
            sf::Vector2f getPosition() { return this->position; };
            sf::Vector2f getSize() {return this->size; };
            sf::Vector2f getOffset() { return this->offset; }
    };
}

#endif