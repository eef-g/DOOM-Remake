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
  if(IsKeyDown(KEY_W)) { this->px += this->pdx * this->speed; this->py += this->pdy * this->speed; }
  if(IsKeyDown(KEY_S)) { this->px -= this->pdx * this->speed; this->py -= this->pdy * this->speed; }
  if(IsKeyDown(KEY_A)) { 
    this->pa -= 0.1;
    if (this->pa < 0) {
      this->pa += 2*PI;
    }
    this->pdx = cos(this->pa) * 5;
    this->pdy = sin(this->pa) * 5;
  }
  if(IsKeyDown(KEY_D)) { 
    this->pa += 0.1;
    if (this->pa > 2*PI) {
      this->pa -= 2*PI;
    }
    this->pdx = cos(this->pa) * 5;
    this->pdy = sin(this->pa) * 5;
  } 
  this->x2 = (this->px + 5) + std::round(32 * cos(this->pa));
  this->y2 = (this->py + 5) + std::round(32 * sin(this->pa));
}

void Player::DrawPlayer() {
  DrawRectangle(this->px, this->py, 10, 10, YELLOW);
  DrawLine(this->px + 5, this->py + 5, this->x2, this->y2, YELLOW);
}
