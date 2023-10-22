#include <iostream>
#include "SDL2/SDL.h"
#include "lib/game.hpp"

int main(int argc, char* argv[]) {
  Game *game = new Game();
  game->init("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);
  while (game->running()) {
    game->handleEvents();
    game->update();
    game->render();
  }
  game->clean();
  return 0;
}