#include "hitbox.hpp"
using namespace CE_Components;

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


    Hitbox::Hitbox(CE_Components::IComponent *sprite, float scale, float offset_x, float offset_y) {
        if (sprite->getType() != "Sprite") {
            throw std::invalid_argument("Hitbox::Hitbox: sprite must be of type Sprite");
        }
        CE_Components::Sprite *sprite_cast = dynamic_cast<CE_Components::Sprite*>(sprite);
        this->shape = sf::RectangleShape(sf::Vector2f(sprite_cast->getSize().x * scale, sprite_cast->getSize().y * scale));
        this->position = sprite_cast->getPosition();
        this->size = sprite_cast->getSize();
        this->offset = sf::Vector2f(offset_x, offset_y);
        this->scale = sf::Vector2f(scale, scale);

        this->shape.setPosition(position + offset);
        this->shape.setFillColor(sf::Color::Transparent);
        this->shape.setSize(sf::Vector2f(size.x * scale, size.y * scale));

        this->shape.setOutlineColor(sf::Color::Red);
        this->shape.setOutlineThickness(1.f);
        std::cout << "Hitbox::Hitbox: " << this->shape.getPosition().x << std::endl;
    }

    Hitbox::Hitbox() {}

    // Destructor
    Hitbox::~Hitbox() {}

    // Functions
    void Hitbox::update(float frameTime) {
        this->shape.setPosition(this->position + this->offset);
    }

    void Hitbox::render(sf::RenderTarget *target) {
        target->draw(shape);
    }

    bool Hitbox::intersects(Hitbox *other) {
        return shape.getGlobalBounds().intersects(other->shape.getGlobalBounds());
    }

}