#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <raylib-cpp.hpp>
#include "math.h"
#include "rlgl.h"
#include "raymath.h"
#include "raylib.h"


class Player {
private:
  float px,py, pdx, pdy, pa;
  float x2, y2;
  float speed;

public:
  Player();
  Player(float x, float y);
  void DrawPlayer();
  void MovePlayer();

  float GetAngle() { return this->pa; }
  Vector2 GetPosition() { return (Vector2){this->px, this->py}; }
};

#endif
