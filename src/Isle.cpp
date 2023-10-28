#include "Isle.hpp"
using namespace IsleGame;

MainGame::MainGame() {
    this->init();
}

void MainGame::init() {
    // This is where we will initialize the game and insert any game objects
    // into the game object vector.

    /*
        gameObject insertion
    */
    TestObj *gameObject = new TestObj();
    this->game.addGameObject(gameObject);
    // this->game.addGameObject(gameObject);
}

void MainGame::run() {
    // This is where we will run the game loop.
    this->game.run();
}