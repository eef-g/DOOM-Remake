#include "settings.hpp"
#include <iostream>
#include <raylib.h>

int main() {
  const int screenWidth = 800;
  const int screenHeight = 600;

  InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}

// int main() {
//   // Initialization
//   CapulusEngine engine = CapulusEngine("wad/doom1.wad");
//   SetConfigFlags(FLAG_WINDOW_RESIZABLE);
//   raylib::Window w(engine.GetScreenWidth(), engine.GetScreenHeight(), "Example");
//   Camera2D cam = { 0 };
//   cam.zoom = 1;

//   SetTargetFPS(60);

//   // Main game loop
//   rlImGuiSetup(true);


//   while (!w.ShouldClose()) // Detect window close button or ESC key
//   {
//     // Draw
//     BeginDrawing();
//     ClearBackground(BLACK);
//     BeginMode2D(cam);
//     rlImGuiBegin();

//     engine.draw();
//     bool open = true;
//     // ImGui::ShowDemoWindow(&open);
//     // engine.debugMenu.Show();

//     rlImGuiEnd();    
//     EndDrawing();
//   }

//   rlImGuiShutdown();

//   CloseWindow();

//   return 0;
// }
