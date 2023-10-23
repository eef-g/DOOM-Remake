#include "player.hpp"

// Private functions
void Player::initVariables() {
    this->movementSpeed = sf::Vector2f(10.f, 10.f);
    if (!this->texture.loadFromFile("assets/character_single.png")) {
        std::cout << "ERROR::PLAYER::INITVARIABLES::Failed to load texture" << std::endl;
    } else {
        this->sprite.setTexture(texture);
        std::cout << "Loaded texture" << std::endl;
    }
}


// Constructors/Destructors
Player::Player() {
    this->initVariables();
}

Player::~Player() {

}

// Accessors
const sf::Vector2f& Player::getPos() const {
    return this->sprite.getPosition();
}

// Functions
void Player::move(const float x, const float y) {
    this->sprite.move(this->movementSpeed.x * x, this->movementSpeed.y * y);
}

void Player::update() {
}

void Player::render(sf::RenderTarget* target) {
    target->draw(this->sprite);
}
