#ifndef HITBOX_HPP
#define HITBOX_HPP

#include <iostream>
#include "component.hpp"
#include <SFML/Graphics.hpp>

class Hitbox : public Component{
    private:
        // Variables
        sf::RectangleShape shape;
        sf::Vector2f size;
        sf::Vector2f offset;
        sf::Vector2f scale;
        float rotation;
    public:
        // Constructor
        Hitbox(
            sf::RectangleShape shape,
            sf::Vector2f position,
            sf::Vector2f size,
            sf::Vector2f offset,
            sf::Vector2f scale, 
            float rotation, 
            bool debug=false
        );

        Hitbox();
        // Destructor
        virtual ~Hitbox() override;

        // Variables
        sf::Vector2f position;

        // Functions
        void update(float frameTime) override;
        void render(sf::RenderTarget *target) override;
        bool intersects(Hitbox *other);
        sf::Vector2f getPosition();
        sf::Vector2f getSize();
        sf::Vector2f getOffset();
        sf::Vector2f getScale();
        float getRotation();
};

#endif