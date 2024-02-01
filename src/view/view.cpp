#include "view.hpp"

namespace dv {
    View::View() {
        this->controller = new dc::Controller();
    };

    void View::runGame() {
        // Window setup
        SetConfigFlags(FLAG_WINDOW_RESIZABLE );
        SetExitKey(0);
        InitWindow(this->controller->GetScreenHeight(), this->controller->GetScreenWidth(), "Doom Clone");
        SetTargetFPS(this->controller->GetMaxFPS());
        Image icon = LoadImage("resources/default_resources/doom_clone.png");
        SetWindowIcon(icon);
        UnloadImage(icon);

        

        // TODO: Finish making the different scenes that will be used
        // Scene Setup
        MainMenu menu(this);
        MapTest mapTest(this);
        // Game game(this);
        // PauseMenu pauseMenu(this);
        // GameOver gameOver(this);

        while(!WindowShouldClose()) {
            BeginDrawing();
            ClearBackground(BLACK);
            switch(this->gameState) {
                case GameState::MAIN_MENU:
                    menu.draw();
                    break;
                case GameState::MAP_TESTING:
                    mapTest.draw();
                    break;
                case GameState::GAME:
                    break;
                case GameState::PAUSE_MENU:
                    break;
                case GameState::GAME_OVER:
                    break;
            }
            EndDrawing();

            switch(this->gameState) {
                case GameState::MAIN_MENU:
                    menu.update();
                    break;
                case GameState::MAP_TESTING:
                    mapTest.update();
                    break;
                case GameState::GAME:
                    // controller->update();
                    break;
                case GameState::PAUSE_MENU:
                    break;
                case GameState::GAME_OVER:
                    break;
            }
        }

        CloseWindow();
    }
}