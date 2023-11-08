#include "player.hpp"
#include "Color.hpp"
#include "Vector2.hpp"
#include "raylib.h"
#include "raymath.h"
#include <cmath>
#include <iostream>
#include <math.h>

Player::Player() {}
Player::Player(float x, float y) {
  this->px = x;
  this->py = y;
  this->speed = 0.5f;
  this->pa = 0.0f;
  this->pdx = cos(this->pa)*5;
  this->pdy = sin(this->pa)*5;

  // Point-slope form stuff
  this->x2 = (this->px + 5) + std::round(32 * cos(this->pa));
  this->y2 = (this->py + 5) + std::round(32 * sin(this->pa));
}

void Player::MovePlayer() {
  float fps = GetFrameTime() * 50;
  
  if(IsKeyDown(KEY_A)) { 
    this->pa -= 0.1 * fps;
    if (this->pa < 0) {
      this->pa += 2*PI;
    }
    this->pdx = cos(this->pa) * 5;
    this->pdy = sin(this->pa) * 5;
  }
  if(IsKeyDown(KEY_D)) { 
    this->pa += 0.1 * fps;
    if (this->pa > 2*PI) {
      this->pa -= 2*PI;
    }
    this->pdx = cos(this->pa) * 5;
    this->pdy = sin(this->pa) * 5;
  } 

  // These variables control how close we can get to the wall
  int xo = 0; if(this->pdx<0) { xo = -20; } else { xo = 20; }
  int yo = 0; if (this->pdy<0) {yo = -20; } else { yo = 20; }
  int ipx = this->px/64.0, ipx_add_xo=(px+xo)/64.0, ipx_sub_xo=(px-xo)/64.0;
  int ipy = this->py/64.0, ipy_add_yo = (py+yo)/64.0, ipy_sub_yo = (py-yo)/64.0;
  
  // Change these later. Only hard coded for the example
  int mapY = 8;
  int mapX = 8;
  int mapS = 64;
  if(IsKeyDown(KEY_W)) { 
    if(this->map[ipy*mapX+ipx_add_xo]==0) { 
      this->px += this->pdx * this->speed * fps;
    }
    if(this->map[ipy_add_yo*mapX+ipx]==0) {
      this->py += this->pdy * this->speed * fps;
    }
  }
  if(IsKeyDown(KEY_S)) { 
    if(this->map[ipy*mapX+ipx_sub_xo]==0) { 
      this->px -= this->pdx * this->speed * fps;
    }
    if(this->map[ipy_sub_yo*mapX+ipx]==0) {
      this->py -= this->pdy * this->speed * fps;
    }
  }
  this->x2 = (this->px + 5) + std::round(32 * cos(this->pa));
  this->y2 = (this->py + 5) + std::round(32 * sin(this->pa));
}

void Player::DrawPlayer() {
  DrawRectangle(this->px, this->py, 10, 10, YELLOW);
  DrawLine(this->px + 5, this->py + 5, this->x2, this->y2, YELLOW);
}
