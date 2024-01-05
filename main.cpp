#include "src/model.hpp"
#include <iostream>

int main() {
  doom::Model model = doom::Model();
  model.runGame();
  return 0;
}



#pragma region old_main
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
#pragma endregion
