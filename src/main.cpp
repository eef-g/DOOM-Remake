#include "raylib.h"
#include <raylib-cpp.hpp>
#include "player.hpp"
#include "camera.hpp"

void DrawMap2D(int* map) {
  int x, y, x0, y0;
  Color dispColor;
  for(y=0;y<8;y++) {
    for(x=0;x<8;x++) {
      if (map[y*8+x]==1) { dispColor = WHITE; } else { dispColor = BLACK;}
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
  raylib::Window w(screenWidth, screenHeight, "Example");
  Player* p = new Player(64*4, 64*3);  
  int map[] = 
    {
      1,1,1,1,1,1,1,1,
      1,0,0,1,0,0,1,1,
      1,1,0,0,0,0,0,1,
      1,0,1,0,0,0,0,1,
      1,0,0,0,1,1,0,1,
      1,0,0,0,1,0,0,1,
      1,0,0,0,1,0,0,1,
      1,1,1,1,1,1,1,1,
    };
  

  SetTargetFPS(60);
  RaycastCam camera = RaycastCam(p, map);
  camera.setMapSize(8, 8);
  // Main game loop
  while (!w.ShouldClose()) // Detect window close button or ESC key
  {
    // Update
    p->MovePlayer();

    // Draw
    BeginDrawing();
    ClearBackground(GRAY);

    DrawMap2D(map);
    p->DrawPlayer();
    camera.DrawRays();

    EndDrawing();
  }
  return 0;
}
