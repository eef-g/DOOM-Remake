#ifndef CAM_HPP
#define CAM_HPP
#include "player.hpp"
#include "math.h"
#ifndef M_PI
#define M_PI 3.14159265358979323846 
#endif

// Include the texture h files
#include "../assets/checkerboard.h"
#include "../assets/brick.h"
#include "../assets/door.h"

class RaycastCam {
private:
int num_rays = 60;
Player* player;
int* map;
int mapX, mapY, mapS;

public:
  RaycastCam() {};
  RaycastCam(Player* player, int* map);
  
  void DrawMap2D();
  void DrawRays();

  void setMapSize(int x, int y) { this->mapX = x; this->mapY = y; this->mapS = x * y; }
};

#endif
