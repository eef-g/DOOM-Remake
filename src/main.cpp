#include "raylib.h"
#include <raylib-cpp.hpp>
#include <raymath.h>
#include <rlImGui.h>
#include <imgui.h>

#include "engine/capulus_engine.hpp"
#include "settings.hpp"

int main() {
  
  // Initialization
  CapulusEngine engine = CapulusEngine("wad/doom1.wad");
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  raylib::Window w(engine.GetScreenWidth(), engine.GetScreenHeight(), "Example");
  Camera2D cam = { 0 };
  cam.zoom = 1;

  SetTargetFPS(60);

  // Main game loop
  rlImGuiSetup(true);


  while (!w.ShouldClose()) // Detect window close button or ESC key
  {
    // Update
    // float mouseDelta = GetMouseWheelMove();

    // float newZoom = cam.zoom + mouseDelta * 0.01f;
    // if (newZoom <= 0) {
    //   newZoom = 0.01f;
    // }
    
    // cam.zoom = newZoom;




    // Draw
    BeginDrawing();
    ClearBackground(BLACK);
    BeginMode2D(cam);
    rlImGuiBegin();

    engine.draw();
    bool open = true;
    ImGui::ShowDemoWindow(&open);


    rlImGuiEnd();    
    EndDrawing();
  }

  rlImGuiShutdown();

  CloseWindow();

  return 0;
}
