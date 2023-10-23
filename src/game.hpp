#ifndef GAME_HPP
#define GAME_HPP

/*
    The Game class acts as a container for all of the game's logic.
    It will contain the game loop, and will be responsible for updating
    and rendering all of the game's objects.
*/

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


// Pro-tip: Press 'CRTL+.' to automatically create the function definition in the cpp file
class Game {
    private:
        // Variables
        sf::RenderWindow* window;
        sf::Event ev;
        sf::VideoMode videoMode;

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
        void pollEvents();
        void update();
        void render();

};
#endif