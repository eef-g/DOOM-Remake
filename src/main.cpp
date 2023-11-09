#include "raylib.h"
#include <raylib-cpp.hpp>
#include "player.hpp"
#include "camera.hpp"

void DrawMap2D(int* map) {
  int x, y, x0, y0;
  Color dispColor;
  for(y=0;y<8;y++) {
    for(x=0;x<8;x++) {
      if (map[y*8+x]>0) { dispColor = WHITE; } else { dispColor = BLACK;}
      x0=x*64;
      y0 = y*64;
      DrawRectangle(x0, y0, 63, 63, dispColor);
    }
  }
}

int main() {
  
  // Initialization
  int screenWidth = 1024;
  int screenHeight = 512;
  SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  raylib::Window w(screenWidth, screenHeight, "Example");
  

  Player* p = new Player(64*4, 64*3);  
  // Map for the walls
  int mapW[] = 
    {
      1,1,1,1,1,1,1,1,
      1,0,0,1,0,0,1,1,
      1,1,0,0,0,0,0,1,
      1,0,1,0,0,0,0,1,
      1,0,0,0,2,2,0,2,
      1,0,0,0,2,0,0,2,
      1,0,0,0,2,0,0,2,
      1,1,1,1,2,2,2,2,
    };
  
  p->SetMap(mapW);

  SetTargetFPS(60);
  RaycastCam camera = RaycastCam(p, mapW);

  camera.setMapSize(8, 8);


  // Main game loop
  while (!w.ShouldClose()) // Detect window close button or ESC key
  {
    // Update
    p->MovePlayer();

    // Draw
    BeginDrawing();
    ClearBackground(GRAY);

    DrawMap2D(mapW);
    p->DrawPlayer();
    camera.DrawRays();

    EndDrawing();
  }
  return 0;
}
