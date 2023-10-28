#include "game.hpp"

namespace CapulusEngine {
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

    /// @brief Runs the game loop
    void Game::run() {
        // Set up everthing to calculate the delta time
        sf::Clock clock;
        float deltaTime = 0.f;
        float maxFPS = 60.f;
        float frameTime = 1.f / maxFPS;

        // Game loop
        while (this->running()) {
            deltaTime += clock.restart().asSeconds();
            this->pollEvents();
            while (deltaTime >= frameTime) {
                // Actual update logic
                this->update(frameTime);
                deltaTime -= frameTime;

                // Sleep for 10 milliseconds to prevent the CPU from being overworked
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
            // Whenever the update logic is done, render the frame
            this->render();
        }
    }

    void Game::addGameObject(GameObject* gameObject) {
        this->gameObjects.push_back(gameObject);
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
                default:
                    break;
            }
        }
    }

    /// @brief Runs the game logic for each frame in the game loop
    void Game::update(float frameTime) {
        // Get the mouse position in the world (Can be used for mouse interaction)
        // sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);
        // sf::Vector2f worldPos = this->window->mapPixelToCoords(mousePos);

        // Update gameObjects
        for(auto &gameObject : this->gameObjects) {
            gameObject->update(frameTime);
        }
    }

    /// @brief Runs the rendering logic for each frame in the game loop
    void Game::render() {
        // Clear the window & update view
        this->window->clear(sf::Color(0, 153, 219, 255));
        this->window->setView(this->view);

        // Render items -- Make sure that the bototm-most layer is rendered first
        for(auto &gameObject : this->gameObjects) {
            gameObject->render(this->window);
        }
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
        this->videoMode.width = 854;



        this->window = new sf::RenderWindow(this->videoMode, "The Isle", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);

        // Initialize the view
        this->view.setSize(sf::Vector2f(this->videoMode.width, this->videoMode.height));
        this->view.setCenter(sf::Vector2f(this->videoMode.width / 2.f, this->videoMode.height / 2.f));
        this->window->setView(this->view);


        // Initialize the cursor
        sf::Image cursorImage;
        cursorImage.loadFromFile("assets/cursor.png");
        this->cursor.loadFromPixels(cursorImage.getPixelsPtr(), cursorImage.getSize(), sf::Vector2u(0, 0));
        this->window->setMouseCursor(this->cursor);
    }
}