#ifndef CE_GAME_HPP
#define CE_GAME_HPP

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
#include <vector>
#include <chrono>
#include <thread>

#include "gameobject.hpp"

namespace CapulusEngine {
    /// @brief The Game class acts as a container for all of the game's logic.
    class Game {
        private:
            // Window handling
            sf::RenderWindow* window;
            sf::Event ev;
            sf::VideoMode videoMode;
            sf::Cursor cursor;
            
            // View handling
            sf::View view;

            // Objects
            std::vector<GameObject*> gameObjects;

            // Functions
            void initVariables();
            void initWindow();
                // These are used in the run function
            void pollEvents();
            void update(float frameTime);
            void render();
        public:
            // Constructor
            Game();
            // Destructor
            virtual ~Game();

            // Accessors
            const bool running() const;
            
            // Functions
            void run();
            void addGameObject(GameObject* gameObject);
            
    };
}
#endif