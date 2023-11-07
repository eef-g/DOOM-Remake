#ifndef CAM_HPP
#define CAM_HPP
#include "player.hpp"
#include "math.h"

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
