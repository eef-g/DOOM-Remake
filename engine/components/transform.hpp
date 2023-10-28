#ifndef CE_TRANSFORM_HPP
#define CE_TRANSFORM_HPP

#include "ce_components.hpp"

namespace CE_Components {
    class Transform : public IComponent {
        private:
            // Variables
            sf::Vector2f position;
            sf::Vector2f scale;
            float rotation;
        public:
            // Constructor
            Transform(
                sf::Vector2f position,
                sf::Vector2f scale,
                float rotation=0.0f
            );
            Transform();
            // Destructor
            virtual ~Transform() override;

            // Functions
            void update(float frameTime) override;
            void render(sf::RenderTarget *target) override;

            // Getters
            sf::Vector2f getPosition() { return this->position; };
            sf::Vector2f getScale() { return this->scale; };
            float getRotation() { return this->rotation; };
    };
}

#endif