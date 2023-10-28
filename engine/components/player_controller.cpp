#include "player_controller.hpp"
using namespace CE_Components;

namespace CE_Components {
    // Constructor / Destructor
    PlayerController::PlayerController(std::string texturePath, sf::Vector2f imageSize) {
        CE_Components::Sprite *sprite = new CE_Components::Sprite(texturePath, imageSize);
        CE_Components::Hitbox *hitbox = new CE_Components::Hitbox(sprite, 0.1f, 0.0f, 0.0f);

        this->components.push_back(sprite);
        this->components.push_back(hitbox);

        this->initVariables();
        this->initComponents();
    }

    PlayerController::PlayerController() {
        this->initVariables();
        this->initComponents();
    }


    // Functions
    void PlayerController::initVariables() {
        this->speed = 100.f;
        this->velocity = sf::Vector2f(0.f, 0.f);
    }

    void PlayerController::initComponents() {}

    void PlayerController::updateVelocity(float frameTime) {
        // Reset the velocity
        this->velocity = sf::Vector2f(0.f, 0.f);

        // Check for input
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            this->velocity.y -= this->speed * frameTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            this->velocity.x -= this->speed * frameTime;
            this->setSpriteScale(-1.f, 1.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            this->velocity.y += this->speed * frameTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            this->velocity.x += this->speed * frameTime;
            this->setSpriteScale(1.f, 1.f);
        }
    }


    void PlayerController::setOffset(float offset_x, float offset_y) {
        CE_Components::Hitbox *hitbox = dynamic_cast<CE_Components::Hitbox*>(this->components[1]);
        hitbox->setOffset(sf::Vector2f(offset_x, offset_y));
    }

    void PlayerController::setSpriteScale(float scale_x, float scale_y) {
        CE_Components::Sprite *sprite = dynamic_cast<CE_Components::Sprite*>(this->components[0]);
        sprite->setScale(sf::Vector2f(scale_x, scale_y));
    }

    void PlayerController::update(float frameTime) {
        this->updateVelocity(frameTime);
        // Convert each component to their parent class and set the new position
        for (auto component : this->components) {
            if (component->getType() == "Sprite") {
                CE_Components::Sprite *sprite = dynamic_cast<CE_Components::Sprite*>(component);
                sprite->setPosition(sprite->getPosition() + this->velocity);
            }
            if (component->getType() == "Hitbox") {
                CE_Components::Hitbox *hitbox = dynamic_cast<CE_Components::Hitbox*>(component);
                hitbox->setPosition(hitbox->getPosition() + this->velocity);
            }
            component->update(frameTime);
        } 
        
    }

    void PlayerController::render(sf::RenderTarget* target) {
        for (auto component : this->components) {
            component->render(target);
        }
    }
}