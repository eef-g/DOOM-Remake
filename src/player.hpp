#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

/*
    The Player class acts as a container for all of the player's logic.
    It will contain the player's movement, and will be responsible for updating
    and rendering the player.
*/
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

            // Movement
        float movementSpeed;
        sf::Vector2f moveDir;
        sf::Vector2f velocity;

        // Functions
        void initVariables();
        void updateAnimation(float deltaTime);
        void updateVelocity();
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