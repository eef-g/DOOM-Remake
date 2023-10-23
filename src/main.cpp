#include <iostream>
#include "game.hpp"

int main() {
    // Initialize the game engine
    Game game;

    // Game loop
    while (game.running()) {
        // Update
        game.update();

        // Render
        game.render();
    }
    
    return 0;
}