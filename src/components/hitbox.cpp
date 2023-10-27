#include "hitbox.hpp"

// Constructor
Hitbox::Hitbox(
    sf::RectangleShape shape, 
    sf::Vector2f position, 
    sf::Vector2f size, 
    sf::Vector2f offset, 
    sf::Vector2f scale, 
    float rotation, 
    bool debug
) {
    this->shape = shape;
    this->position = position;
    this->size = size;
    this->offset = offset;
    this->scale = scale;
    this->rotation = rotation;
    this->shape.setFillColor(sf::Color::Transparent);

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
    sf::Vector2f newSize = sf::Vector2f(size.x * scale.x, size.y * scale.y);
    shape.setSize(newSize);
    shape.setRotation(rotation);
}

void Hitbox::render(sf::RenderTarget *target) {
    target->draw(shape);
}

bool Hitbox::intersects(Hitbox *other) {
    return shape.getGlobalBounds().intersects(other->shape.getGlobalBounds());
}

sf::Vector2f Hitbox::getPosition() {
    return position;
}

sf::Vector2f Hitbox::getSize() {
    return size;
}

sf::Vector2f Hitbox::getOffset() {
    return offset;
}

sf::Vector2f Hitbox::getScale() {
    return scale;
}

float Hitbox::getRotation() {
    return rotation;
}
