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
        sf::Vector2f movementSpeed;
        sf::Sprite sprite;
        sf::Texture texture;
        sf::Vector2f moveDir;

        // Functions
        void initVariables();

    public:
        // Constructor/Destructor
        Player();
        virtual ~Player();

        // Accessors
        const sf::Vector2f& getPos() const;

        // Functions
        void move(const float x, const float y);
        void eventHandler(sf::Event* ev);
        void update();
        void render(sf::RenderTarget* target);
};


#endif