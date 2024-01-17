#include "view.hpp"

namespace dv {
    View::View() {
        this->controller = new dc::Controller();
    };

    void View::runGame() {
        SetConfigFlags(FLAG_WINDOW_RESIZABLE);
        InitWindow(this->controller->GetScreenHeight(), this->controller->GetScreenWidth(), "Doom Clone");
        SetTargetFPS(this->controller->GetMaxFPS());

        MainMenu menu;
        while(!WindowShouldClose()) {
            BeginDrawing();
            ClearBackground(BLACK);
            menu.draw();
            // BeginMode2D(controller.getCamera());
            // controller.draw();
            // EndMode2D();
            EndDrawing();
        }

        CloseWindow();
    }
}