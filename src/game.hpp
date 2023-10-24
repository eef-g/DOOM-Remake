#ifndef GAME_HPP
#define GAME_HPP

/*
    The Game class acts as a container for all of the game's logic.
    It will contain the game loop, and will be responsible for updating
    and rendering all of the game's objects.
*/

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "player.hpp"
#include "tilemap.hpp"

// Pro-tip: Press 'CRTL+.' to automatically create the function definition in the cpp file

/// @brief The Game class acts as a container for all of the game's logic.
class Game {
    private:
        // Window handling
        sf::RenderWindow* window;
        sf::Event ev;
        sf::VideoMode videoMode;
        
        // View handling
        sf::View view;

        // Objects
        Player player = Player();
        Tilemap tilemap = Tilemap();

        // Functions
        void initVariables();
        void initWindow();
    public:
        // Constructor
        Game();
        // Destructor
        virtual ~Game();

        // Accessors
        const bool running() const;
        // Functions
        void run();
        void pollEvents();
        void update(float frameTime);
        void render();
};

#endif