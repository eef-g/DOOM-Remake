#include "model.hpp"
namespace doom {
    Model::Model() {
        this->screenWidth = WIN_W;
        this->screenHeight = WIN_H;
    }

    void Model::runGame() {
        InitWindow(this->screenWidth, this->screenHeight, "Game");
        SetTargetFPS(60);

        while (!WindowShouldClose()) {
            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Game", 190, 200, 20, LIGHTGRAY);
            EndDrawing();
        }

        CloseWindow();
    }
}