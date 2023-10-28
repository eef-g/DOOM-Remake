#ifndef PLAYER_CONTROLLER_HPP
#define PLAYER_CONTROLLER_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "ce_components.hpp"


namespace CE_Components {
    class PlayerController : public IComponent {
        private:
            // Variables

            // Need to make the components in the constructor bc of the way the engine is set up
            std::vector<IComponent*> components; 
                // Movement
            float speed;
            sf::Vector2f velocity;

            // Functions
            void initVariables();
            void initComponents();
            void updateVelocity(float frameTime);

        public:
            // Constructor / Destructor
            PlayerController(std::string texturePath, sf::Vector2f imageSize);
            PlayerController();
            virtual ~PlayerController() override {};

            // Functions
            void update(float frameTime) override;
            void render(sf::RenderTarget* target) override;
            std::string getType() override { return "PlayerController"; };

            // Getters
            sf::Vector2f getVelocity() { return this->velocity; };
            float getSpeed() { return this->speed; };

            // Setters
            void setSpeed(float speed) { this->speed = speed; };
            void setOffset(float offset_x, float offset_y);
            void setSpriteScale(float scale_x, float scale_y);
             

    };
}

#endif