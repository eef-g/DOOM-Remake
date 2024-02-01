#ifndef VIEW_HPP
#define VIEW_HPP

#include <raylib.h>
#include <unistd.h>

#include "../controller/controller.hpp"
#include "main_menu.hpp"
#include "map_test.hpp"

namespace dv {
    enum class GameState {
        MAIN_MENU,
        MAP_TESTING,
        GAME,
        PAUSE_MENU,
        GAME_OVER
    };

    class View {
    private:
        dc::Controller *controller = nullptr;
        GameState gameState = GameState::MAIN_MENU;
    public:
        View();
        ~View() { delete this->controller; };
        void runGame();
        void setGameState(GameState gameState) { this->gameState = gameState; };
        dc::Controller* getController() { return this->controller; };
    };
}

#endif