#include "view.hpp"

namespace dv {
    View::View() {
        this->controller = new dc::Controller();
    };

    void View::runGame() {
        SetConfigFlags(FLAG_WINDOW_RESIZABLE);
        InitWindow(this->controller->GetScreenHeight(), this->controller->GetScreenWidth(), "Doom Clone");
        SetTargetFPS(this->controller->GetMaxFPS());

        MainMenu menu(this);
        while(!WindowShouldClose()) {
            BeginDrawing();
            ClearBackground(BLACK);
            switch(this->gameState) {
                case GameState::MAIN_MENU:
                    menu.draw();
                    break;
                case GameState::GAME:
                    // controller->update();
                    break;
                case GameState::PAUSE_MENU:
                    break;
                case GameState::GAME_OVER:
                    break;
            }
            EndDrawing();
        }

        CloseWindow();
    }
}