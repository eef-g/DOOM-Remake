#include "player.hpp"

// Private functions

/// @brief Initializes the player's variables
void Player::initVariables() {
    this->movementSpeed = 150.f;
    
    // Prep the spritesheet
    this->spriteSheet.loadFromFile("assets/character_sheet.png");
    this->spriteCount = sf::Vector2u(23, 20);
    this->currentSprite = sf::Vector2u(0, 2);

    this->swapAnimationRepeat(IDLE);

    // Prep the uvRect
    this->uvRect.width = this->spriteSheet.getSize().x / float(this->spriteCount.x);
    this->uvRect.height = this->spriteSheet.getSize().y / float(this->spriteCount.y);

    // Prep the shape that is rendered
    this->shape.setTexture(&this->spriteSheet);
    this->shape.setSize(sf::Vector2f(this->uvRect.width, this->uvRect.height));

    sf::FloatRect bounds = this->shape.getLocalBounds();
    this->shape.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
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
            this->mouseInteraction();
        }



        void Player::mouseInteraction() {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                this->swapAnimationSingle(PICKAXE, IDLE);
            }
        }

        /// @brief Updates the player's velocity based on input
        void Player::updateVelocity() {
            // Prep empty velocity vector
            sf::Vector2f velocity(0.f, 0.f);

            // Only calculate player velocity if they can move
            if (this->canMove) {
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                    velocity.y -= 1.f;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                    this->shape.setScale(-1.f, 1.f);
                    velocity.x -= 1.f;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                    velocity.y +=1.f;
                }
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                    this->shape.setScale(1.f, 1.f);
                    velocity.x += 1.f;
                }
                if (velocity.x != 0.f && velocity.y != 0.f) {
                    velocity.x /= sqrt(2.f);
                    velocity.y /= sqrt(2.f);
                }
            }
            // Update player's velocity
            this->velocity = this->movementSpeed * velocity;
            
            // Animation handling
            if (velocity.x == 0.f && velocity.y == 0.f) {
                switch (this->oneshotAnim) {
                    case true:
                        //Nothing happens
                    break;
                    case false:
                        if (this->currentAnimation != IDLE) {
                            this->swapAnimationRepeat(IDLE);
                        }
                    break;
                }
            } else {
                switch (this->oneshotAnim) {
                    case true:
                        //Nothing happens
                    break;
                    case false:
                        if (this->currentAnimation != RUNNING) {
                            this->swapAnimationRepeat(RUNNING);
                        }
                    break;
                }
            }
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
                if (this->currentSprite.x < this->animFrames) {
                    this->currentSprite.x++;
                } else {
                    if (this->oneshotAnim) { this->swapAnimationRepeat(this->queuedAnimation); }
                    else { this->currentSprite.x = 0; }
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
            if(!this->canMove && this->currentSprite.x == 0) {
                if (this->mousePos.x < this->getPos().x) {
                    if(this->shape.getScale().x > 0.f) {
                        this->shape.setScale(-1.f, 1.f);
                    }
                } else {
                    this->shape.setScale(1.f, 1.f);
                }
            }
            this->shape.setTexture(&this->spriteSheet);
            this->shape.setTextureRect(this->uvRect);
            target->draw(this->shape);
        }

    #pragma endregion


    #pragma region UtilityFunctions
        /*
            Utility functions
        */

       /// @brief Switches the current animation and refreshes the timer
       /// @param animation The animation to switch to
       void Player::swapAnimation(Animations animation) {
            this->animTimer = 0.f;
            this->currentAnimation = animation;
            this->canMove = false;
            switch(animation) {
                case WALK:
                    this->currentSprite = sf::Vector2u(0, 0);
                    this->frameTime = 0.1f;
                    this->animFrames = 6;
                    this->canMove = true;
                    break;
                case CARRY:
                    this->currentSprite = sf::Vector2u(0, 1);
                    this->frameTime = 0.15f;
                    this->animFrames = 7;
                    this->canMove = true;
                    break;
                case IDLE:
                    this->currentSprite = sf::Vector2u(0, 2);
                    this->frameTime = 0.15f;
                    this->animFrames = 5;
                    this->canMove = true;
                    break;
                case WATERING:
                    this->currentSprite = sf::Vector2u(0, 3);
                    this->frameTime = 0.15f;
                    this->animFrames = 4;
                    break;
                case HIT:
                    this->currentSprite = sf::Vector2u(0, 4);
                    this->frameTime = 0.15f;
                    this->animFrames = 5;
                    break;
                case DEATH:
                    this->currentSprite = sf::Vector2u(0, 5);
                    this->frameTime = 0.15f;
                    this->animFrames = 7;
                    break;
                case DOING:
                    this->currentSprite = sf::Vector2u(0, 6);
                    this->frameTime = 0.15f;
                    this->animFrames = 7;
                    break;
                case RUNNING:
                    this->currentSprite = sf::Vector2u(0, 7);
                    this->frameTime = 0.1f;
                    this->animFrames = 7;
                    this->canMove = true;
                    break;
                case JUMPING:
                    this->currentSprite = sf::Vector2u(0, 8);
                    this->frameTime = 0.15f;
                    this->animFrames = 6;
                    this->canMove = true;
                    break;
                case ROLLING:
                    this->currentSprite = sf::Vector2u(0, 9);
                    this->frameTime = 0.15f;
                    this->animFrames = 9;
                    this->canMove = true;
                    break;
                case AXE:
                    this->currentSprite = sf::Vector2u(0, 10);
                    this->frameTime = 0.15f;
                    this->animFrames = 9;
                    break;
                case PICKAXE:
                    this->currentSprite = sf::Vector2u(0, 11);
                    this->frameTime = 0.08f;
                    this->animFrames = 9;
                    break;
                case SWIMMING:
                    this->currentSprite = sf::Vector2u(0, 12);
                    this->frameTime = 0.15f;
                    this->animFrames = 3;
                    this->canMove = true;
                    break;
                case HAMMER:
                    this->currentSprite = sf::Vector2u(0, 13);
                    this->frameTime = 0.15f;
                    this->animFrames = 22;
                    break;
                case SWORD:
                    this->currentSprite = sf::Vector2u(0, 14);
                    this->frameTime = 0.15f;
                    this->animFrames = 9;
                    break;
                case CASTING:
                    this->currentSprite = sf::Vector2u(0, 15);
                    this->frameTime = 0.15f;
                    this->animFrames = 14;
                    break;
                case WAITING:
                    this->currentSprite = sf::Vector2u(0, 16);
                    this->frameTime = 0.15f;
                    this->animFrames = 7;
                    break;
                case CAUGHT:
                    this->currentSprite = sf::Vector2u(0, 17);
                    this->frameTime = 0.15f;
                    this->animFrames = 12;
                    break;
                case REELING:
                    this->currentSprite = sf::Vector2u(0, 18);
                    this->frameTime = 0.15f;
                    this->animFrames = 9;
                    break;
                case SHOVEL:
                    this->currentSprite = sf::Vector2u(0, 19);
                    this->frameTime = 0.15f;
                    this->animFrames = 12;
                    break;
                default:
                    break;
            }
       }

       void Player::swapAnimationRepeat(Animations anim) {
            this->oneshotAnim = false;
            this->swapAnimation(anim);
       }

       void Player::swapAnimationSingle(Animations target_anim, Animations post_anim) {
            this->oneshotAnim = true;        
            this->swapAnimation(target_anim);
            this->queuedAnimation = post_anim;
       }

       void Player::setMousePos(sf::Vector2f mousePos) {
           this->mousePos = mousePos;
       }
    #pragma endregion

#pragma endregion