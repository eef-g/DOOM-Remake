#include "player.hpp"

// Private functions
void Player::initVariables() {
    this->movementSpeed = 150.f;

    if (!this->texture.loadFromFile("assets/character_single.png")) {
        std::cout << "ERROR::PLAYER::INITVARIABLES::Failed to load texture" << std::endl;
    } else {
        this->sprite.setTexture(this->texture);
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
void Player::move(float deltaTime) {
    // Calculate the new position
    sf::Vector2f newPos = this->getPos() + this->velocity * deltaTime;
    // Set new position
    this->sprite.setPosition(newPos);
}

void Player::update(float deltaTime) {
    this->updateVelocity();
    this->move(deltaTime);
}

void Player::updateVelocity() {
    sf::Vector2f velocity(0.f, 0.f);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        velocity.y -= 1.f;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        velocity.x -= 1.f;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        velocity.y += 1.f;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        velocity.x += 1.f;
    }
    this->velocity = this->movementSpeed * velocity;
}


void Player::render(sf::RenderTarget* target) {
    target->draw(this->sprite);
}
