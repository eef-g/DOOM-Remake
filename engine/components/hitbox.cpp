#include "hitbox.hpp"
namespace CE_Components {
    // Constructor
    Hitbox::Hitbox(
        sf::RectangleShape shape, 
        sf::Vector2f position, 
        sf::Vector2f size, 
        sf::Vector2f offset, 
        sf::Vector2f scale, 
        bool debug
    ) {
        this->shape = shape;
        this->position = position;
        this->size = size;
        this->offset = offset;
        this->scale = scale;

        this->shape.setPosition(position + offset);
        this->shape.setFillColor(sf::Color::Transparent);
        this->shape.setSize(sf::Vector2f(size.x * scale.x, size.y * scale.y));

        if (debug) {
            this->shape.setOutlineColor(sf::Color::Red);
            this->shape.setOutlineThickness(1.f);
        }
    }

    Hitbox::Hitbox() {}

    // Destructor
    Hitbox::~Hitbox() {}

    // Functions
    void Hitbox::update(float frameTime) {
        shape.setPosition(position + offset);
    }

    void Hitbox::render(sf::RenderTarget *target) {
        target->draw(shape);
    }

    bool Hitbox::intersects(Hitbox *other) {
        return shape.getGlobalBounds().intersects(other->shape.getGlobalBounds());
    }

}