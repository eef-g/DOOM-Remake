#include "view.hpp"

namespace dv {
    View::View() {
        this->controller = dc::Controller();
    };

    void View::runGame() {
        SetConfigFlags(FLAG_WINDOW_RESIZABLE);
        InitWindow(this->controller.GetScreenHeight(), this->controller.GetScreenWidth(), "Doom Clone");
        SetTargetFPS(this->controller.GetMaxFPS());

        while(!WindowShouldClose()) {
            BeginDrawing();
            ClearBackground(BLACK);
            // BeginMode2D(controller.getCamera());
            // controller.draw();
            // EndMode2D();
            EndDrawing();
        }

        CloseWindow();
    }
}