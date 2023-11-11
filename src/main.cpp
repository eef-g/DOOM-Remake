#include "raylib.h"
#include <raylib-cpp.hpp>
#include "capulus_engine.hpp"

int main() {
  
  // Initialization
  int screenWidth = 1024;
  int screenHeight = 512;
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  raylib::Window w(screenWidth, screenHeight, "Example");


  SetTargetFPS(60);
  CapulusEngine engine = CapulusEngine("wad/doom1.wad");

  // Main game loop



  while (!w.ShouldClose()) // Detect window close button or ESC key
  {
    // Update

    // Draw
    BeginDrawing();
    
    ClearBackground(GRAY);

    EndDrawing();
  }
  return 0;
}
