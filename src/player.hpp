#ifndef PLAYER_HPP
#define PLAYER_HPP

// #include <string>
#include <iostream>
#include <cmath>

#include <SFML/Graphics.hpp>

/// @brief Enum for the different animations the player can have
enum Animations {
    WALK,
    CARRY,
    IDLE,
    WATERING,
    HIT,
    DEATH,
    DOING,
    RUNNING,
    JUMPING,
    ROLLING,
    AXE,
    PICKAXE,
    SWIMMING,
    HAMMER,
    SWORD,
    CASTING,
    WAITING,
    CAUGHT,
    REELING,
    SHOVEL
};

/*
    The Player class acts as a container for all of the player's logic.
    It will contain the player's movement, and will be responsible for updating
    and rendering the player.
*/

/// @brief The Player class acts as a container for all of the player's logic.
class Player {
    private:
        // Variables
            // Spritesheet handling

        sf::RectangleShape shape;
        sf::IntRect uvRect;
        sf::Texture spriteSheet;
        sf::Vector2u spriteCount;
        sf::Vector2u currentSprite;
        int animFrames;
        float animTimer;
        float frameTime;
        Animations currentAnimation;

            // Movement

        float movementSpeed;
        sf::Vector2f moveDir;
        sf::Vector2f velocity;

        // Functions

        void initVariables();
        void updateAnimation(float deltaTime);
        void updateVelocity();
        void swapAnimation(Animations animation);

    public:
        // Constructor/Destructor
        Player();
        virtual ~Player();

        // Accessors
        const sf::Vector2f& getPos() const;

        // Functions
        void move(float deltaTime);
        void update(float deltaTime);

        void render(sf::RenderTarget* target);
};

#endif