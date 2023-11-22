#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include "../wad_classes/data_types.hpp"
#include "../wad_classes/wad_data.hpp"

class Player {
private:
    int16_t x_pos;
    int16_t y_pos;
    int16_t angle;

public:
    Player(THING player_thing);
    Player() {};

    int16_t GetXPos() { return this->x_pos; };
    int16_t GetYPos() { return this->y_pos; };
    int16_t GetAngle() { return this->angle; };

    void SetXPos(int16_t pos) { this->x_pos = pos; };
    void SetYPos(int16_t pos) { this->y_pos = pos; };
    void SetAngle(int16_t angle) { this->angle = angle; };
    void Draw();
};

#endif