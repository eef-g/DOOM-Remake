#ifndef Game_hpp
#define Game_hpp

#include "SDL2/SDL.h"
#include <stdio.h>

class Game {
    public:
        Game();
        ~Game();

        void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
        
        // Handle events
        void handleEvents();
        
        // Goes thru and updates all game objects
        void update();

        // Renders all game objects
        void render();

        // Clean up memory
        void clean();

        bool running() { return isRunning; } 
    private:
        bool isRunning;
        SDL_Window *window;
        SDL_Renderer *renderer;
};

#endif