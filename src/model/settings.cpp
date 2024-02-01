#include "settings.hpp"
int DOOM_RES[] = {320, 200};
int DOOM_W = DOOM_RES[0];
int DOOM_H = DOOM_RES[1];

float SCALE = 5.0f;
int WIN_RES[] = {DOOM_W * SCALE, DOOM_H * SCALE};
int WIN_W = WIN_RES[0];
int WIN_H = WIN_RES[1];

int H_WIDTH = WIN_W / 2;
int H_HEIGHT = WIN_H / 2;

int FPS = 60;