#include "player.hpp"

// Private functions
void Player::initVariables() {
    this->movementSpeed = 150.f;
    
    // Prep the spritesheet
    this->spriteSheet.loadFromFile("assets/character_sheet.png");
    this->spriteCount = sf::Vector2u(23, 20);
    this->currentSprite = sf::Vector2u(0, 2);
    this->animFrames = 5;
    this->frameTime = 0.15f;
    this->animTimer = 0.f;

    // Prep the uvRect
    this->uvRect.width = this->spriteSheet.getSize().x / float(this->spriteCount.x);
    this->uvRect.height = this->spriteSheet.getSize().y / float(this->spriteCount.y);
    std::cout << "Texture Size: " << this->spriteSheet.getSize().x << ", " << this->spriteSheet.getSize().y << std::endl;
    std::cout << "UV Rect: " << this->uvRect.left << ", " << this->uvRect.top << ", " << this->uvRect.width << ", " << this->uvRect.height << std::endl;

    // Prep the shape that is rendered
    this->shape.setTexture(&this->spriteSheet);
    this->shape.setSize(sf::Vector2f(this->uvRect.width, this->uvRect.height));
}


// Constructors/Destructors
Player::Player() {
    this->initVariables();
}

Player::~Player() {

}

// Accessors
const sf::Vector2f& Player::getPos() const { return this->shape.getPosition(); }

#pragma region Functions

    #pragma region UpdateFunctions
        /*
            Update functions
        */

        /// @brief Main update function for the player
        /// @param deltaTime The time between frames
        void Player::update(float deltaTime) {
            this->updateAnimation(deltaTime);
            this->updateVelocity();
            this->move(deltaTime);
        }

        /// @brief Updates the player's velocity based on input
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

        /// @brief Move the player sprite based on it's velocity
        /// @param deltaTime The time between frames
        void Player::move(float deltaTime) {
            // Calculate the new position
            sf::Vector2f newPos = this->getPos() + this->velocity * deltaTime;
            // Set new position
            this->shape.setPosition(newPos);
        }

        /// @brief Updates the player's animation
        /// @param deltaTime The time between frames
        void Player::updateAnimation(float deltaTime) {
            // Update the animation timer
            this->animTimer += deltaTime;
            // If the animation timer is greater than the frame time, update the animation
            if (this->animTimer >= this->frameTime) {
                // Reset the animation timer
                this->animTimer = 0.f;
                // Update the current sprite
                if (this->currentSprite.x < this->animFrames) {
                    this->currentSprite.x++;
                }
                else {
                    this->currentSprite.x = 0;
                }
            }
            // Update the uvRect
            this->uvRect.left = this->currentSprite.x * this->uvRect.width;
            this->uvRect.top = this->currentSprite.y * this->uvRect.height;
        }

    #pragma endregion



    #pragma region RenderFunctions
        /*
            Render functions
        */


        void Player::render(sf::RenderTarget* target) {
            this->shape.setTexture(&this->spriteSheet);
            this->shape.setTextureRect(this->uvRect);
            target->draw(this->shape);
        }

    #pragma endregion

#pragma endregion