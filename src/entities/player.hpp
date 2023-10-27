#ifndef PLAYER_HPP
#define PLAYER_HPP

// #include <string>
#include <iostream>
#include <cmath>

// Include the components we need to use
#include "../components/gameobject.hpp"
#include "../components/hitbox.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
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
class Player : public GameObject {
    private:
        // Variables
            // Spritesheet handling

        sf::RectangleShape shape;
        sf::IntRect uvRect;
        sf::Texture spriteSheet;
        sf::Vector2u spriteCount;
        sf::Vector2u currentSprite;
        

            // Animation logic
        int animFrames = 0;
        float animTimer = 0.f;
        float frameTime =0.f;
        bool oneshotAnim = false;
        Animations currentAnimation;
        Animations queuedAnimation;
        sf::Vector2f mousePos;

            // Movement
        bool canMove = true;
        float movementSpeed = 0.f;
        sf::Vector2f moveDir;
        sf::Vector2f velocity;

            // GameObject Components
        Hitbox* hitbox;


        // Functions

        void initVariables();
        void updateAnimation(float deltaTime);
        void updateVelocity();
        void swapAnimation(Animations animation);
        void mouseInteraction();
        void swapAnimationRepeat(Animations anim);
        void swapAnimationSingle(Animations target_anim, Animations post_anim);
    public:
        // Constructor/Destructor
        Player();
        virtual ~Player();

        // Accessors
        const sf::Vector2f& getPos() const;

        // Functions
        void setMousePos(sf::Vector2f mousePos);

        void move(float deltaTime);
        void update(float deltaTime);
        void render(sf::RenderTarget* target);
};

#endif