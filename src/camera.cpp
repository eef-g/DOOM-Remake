#include "camera.hpp"
#include <cmath>

RaycastCam::RaycastCam(Player* player, int* map) {
  this->player = player;
  this->map = map;
  this->mapX = 8;
  this->mapY = 8;
  this->mapS = this->mapX * this->mapY;
}

// Helper Functions

float DegToRad(float a) { return a*M_PI/180.0; }
float RadToDeg(float a) { return a*180.0/M_PI; }

int FixAng(int a) {
  if(a>359) { a -= 360; }
  if (a<0) { a += 360; }
  return a;
}

float Distance(int ax,int ay,int bx,int by,int ang) {
  return cos(DegToRad(ang)) * (bx-ax) - sin(DegToRad(ang)) * (by-ay);
}

void RaycastCam::DrawRays() {
  // r -- Current ray
  // mx -- ray hit at the map X coord
  // my -- ray hit at the map Y coord 
  int r, mx, my, mp, dof, side;
  float px, py, vx, vy, rx, ry, ra, xo, yo, disV, disH;
  Color drawColor;
  float pa = RadToDeg(this->player->GetAngle()) * -1;
  ra = FixAng(pa + 30);
  px = this->player->GetPosition().x + 5;
  py = this->player->GetPosition().y + 5;
  // Calculate Rays
  for(r = 0; r < 60; r++) {
    // Get texture number
    int vmt=0, hmt=0;

    // ---- Vertical Rays ---- 

    dof = 0; side = 0; disV = 1000000;
    float Tan = tan(DegToRad(ra));
    // Looking left
    if (cos(DegToRad(ra)) > 0.001) { rx = (((int)px>>6)<<6) + 64;   ry = (px - rx)*Tan+py; xo = 64; yo = -xo*Tan;}
    // Looking right
    else if (cos(DegToRad(ra)) < -0.001) { rx = (((int)px>>6)<<6) - 0.0001; ry = (px - rx) * Tan + py; xo = -64; yo = -xo * Tan; }
    // Looking up or down. No Hit
    else {rx = px; ry = py; dof = 8; }

    while(dof <8) {
      mx = (int)(rx)>>6; my = (int)(ry)>>6; mp=my*this->mapX+mx;
      // Hit
      if(mp > 0 && mp < this->mapX*this->mapY && this->map[mp]>0) { vmt = this->map[mp]; dof = 8; disV = cos(DegToRad(ra)) *(rx - px) - sin(DegToRad(ra)) * (ry - py); }

      // Check next horizontal
      else { rx += xo; ry += yo; dof += 1; }
    }
    vx = rx; vy = ry;

    // ---- Horizontal Rays ----
    dof = 0; disH = 1000000;
    Tan = 1.0/Tan;

    // Looking up
    if (sin(DegToRad(ra)) > 0.001) { ry = (((int)py>>6)<<6) - 0.0001; rx = (py-ry) * Tan + px; yo = -64; xo = -yo * Tan; }
    // Looking down
    else if (sin(DegToRad(ra)) < -0.001) { ry = (((int)py>>6)<<6) + 64; rx = (py - ry)* Tan + px; yo = 64; xo = -yo * Tan; }
    // Looking left or right. No Hit
    else { rx = px; ry = py; dof = 8; }

    while(dof < 8) {
      // Check next horizontal
      mx = (int)(rx)>>6; my = (int)(ry)>>6; mp = my * this->mapX + mx;
      if(mp>0 && mp<this->mapX*this->mapY && this->map[mp]>0) { hmt = this->map[mp]; dof = 8; disH = cos(DegToRad(ra)) * (rx - px) - sin(DegToRad(ra)) * (ry - py); }
      else { rx += xo; ry += yo; dof += 1; }
    }
    
    float shade = 1;
    if(disV<disH) { 
        rx = vx; 
        ry = vy; 
        disH = disV;
        shade = 0.5;
        hmt = vmt; 
    }

    // Draw 2D Rays
    DrawLine(px, py, rx, ry, RED); // Draw the ray
    
    int ca = FixAng(pa - ra); disH = disH*cos(DegToRad(ca));
    
    int lineH = (this->mapS * 320)/(disH); 
    float ty_step = 32.0/(float)lineH;
    float ty_off = 0;
    if (lineH>320){ ty_off = (lineH - 320)/2.0; lineH = 320; }
    
    int lineOff = 160 - (lineH>>1);
    float startX = r * 8 + 530;
    Vector2 startPos = (Vector2){startX, (float)lineOff};
    Vector2 endPos = (Vector2){startX, (float)lineH+lineOff};

    // Draw 3D lineH
    float ty = ty_off * ty_step;
    float tx;
    if(shade == 1) { tx = (int)(rx/2.0) % 32; if(ra>180) { tx=31-tx; } }
    else { tx = (int)(ry/2.0) % 32; if(ra>90 && ra<270) { tx = 31-tx; } }

    // Figure out which texture we're going to use
    int* texture;
    switch (hmt) {
      case 1:
        texture = checkerboard;
        break;
      case 2:
        texture = brick;
        break;
      case 4:
        texture = door;
        break;
      default:
        texture = checkerboard;
        break;
    }


    for(int y = 0; y<lineH;y++) {
      float c = texture[(int)(ty)*32 + (int)(tx)];
      if(c == 0) { 
        unsigned char r = static_cast<unsigned char>(0x00 * shade);
        unsigned char g = static_cast<unsigned char>(0x00 * shade);
        unsigned char b = static_cast<unsigned char>(0x00 * shade);
        drawColor = {r, g, b, 0xff};
      }
      else { 
        unsigned char r = static_cast<unsigned char>(0xff * shade);
        unsigned char g = static_cast<unsigned char>(0xff * shade);
        unsigned char b = static_cast<unsigned char>(0xff * shade);
        drawColor = {r, g, b, 0xff};
      }
      // Treating this as drawing an 8x8 pixel
      DrawRectangle(startX, y+lineOff, 8, 8, drawColor);
      ty += ty_step;
    }

    // Prep ra for next loop
    ra = FixAng(ra - 1);
  }
}