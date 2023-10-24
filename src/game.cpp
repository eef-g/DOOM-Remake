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

void Game::run() {
    sf::Clock clock;
    float deltaTime = 0.f;
    float maxFPS = 60.f;
    float frameTime = 1.f / maxFPS;
    while (this->running()) {
        deltaTime += clock.restart().asSeconds();
        this->pollEvents();
        while (deltaTime >= frameTime) {
            this->update(frameTime);
            deltaTime -= frameTime;
        }
        this->render();
    }
}


/// @brief Polls events from the window
void Game::pollEvents() {
    // Event Polling
    while (this->window->pollEvent(this->ev)) {
        switch (this->ev.type) {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if (this->ev.key.code == sf::Keyboard::Escape) {
                    this->window->close();
                }
                break;
        }
    }
}

/// @brief Runs the game logic for each frame in the game loop
void Game::update(float frameTime) {
    sf::Vector2f velocity(0.f, 0.f);
    this->player.update(frameTime);
}

/// @brief Runs the rendering logic for each frame in the game loop
void Game::render() {
    // Clear the window
    this->window->clear(sf::Color(135, 207, 94, 255));
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
    this->videoMode.height = 720;
    this->videoMode.width = 1280;

    window = new sf::RenderWindow(this->videoMode, "The Isle", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
}