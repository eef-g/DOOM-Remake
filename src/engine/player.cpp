#include "player.hpp"

Player::Player(THING player_thing) {
    this->x_pos = player_thing.x_pos;
    this->y_pos = player_thing.y_pos;
    this->angle = player_thing.angle;
}

void Player::Draw() {
    DrawCircle(this->x_pos, this->y_pos, 5.0, GREEN);
}