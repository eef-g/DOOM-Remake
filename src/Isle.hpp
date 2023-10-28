#ifndef ISLE_HPP
#define ISLE_HPP
#include "game/IsleGame.hpp"
using namespace IsleGame;

class MainGame{
    private:
        // Variables
        Game game;
    public:
        MainGame(); 
        virtual ~MainGame() {};

        // Functions
        void run();
        void init();
};

#endif