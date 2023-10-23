#include "game.hpp"


// Constructor / Destructor
Game::Game() {
    this->initVariables();
    this->initWindow();
}

Game::~Game() {
    delete this->window;
}

/*
    Public Functions
*/

/// @brief Returns whether the game is running or not
const bool Game::running() const { return this->window->isOpen(); }

/// @brief Polls events from the window
void Game::pollEvents() {
    // Event Polling
    while (this->window->pollEvent(this->ev)) {
        switch (this->ev.type) {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                float x_delta = 0;
                float y_delta = 0;
                if (this->ev.key.code == sf::Keyboard::Escape) {
                    this->window->close();
                }
                if (this->ev.key.code == sf::Keyboard::W) {
                    y_delta -= 1.f;
                }
                if (this->ev.key.code == sf::Keyboard::A) {
                    x_delta -= 1.f;
                }
                if (this->ev.key.code == sf::Keyboard::S) {
                    y_delta += 1.f;
                }
                if (this->ev.key.code == sf::Keyboard::D) {
                    x_delta += 1.f;
                }
                this->player.move(x_delta, y_delta);
                break;
        }
    }
}

/// @brief Runs the game logic for each frame in the game loop
void Game::update() {
    this->pollEvents();
}

/// @brief Runs the rendering logic for each frame in the game loop
void Game::render() {
    // Clear the window
    this->window->clear(sf::Color(255, 0, 0, 255));
    // Render items
    this->player.render(this->window);
    // Display items
    this->window->display();
}

/*
    Private Functions
*/


/// @brief Initializes the game's variables
void Game::initVariables() {
    this->window = nullptr;
}

/// @brief Initializes the game's window
void Game::initWindow() {
    this->videoMode.height = 480;
    this->videoMode.width = 640;

    window = new sf::RenderWindow(this->videoMode, "The Isle", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
}