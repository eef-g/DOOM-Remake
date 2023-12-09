#include "capulus_engine.hpp"

CapulusEngine::CapulusEngine(std::string wad_path) {
    this->wad_path = wad_path;
    this->map_name = "E1M2";
    this->init();
}

void CapulusEngine::init() {
    this->wad_data = WADData(this->wad_path, this->map_name);
    this->renderer = MapRenderer(this->wad_data);
    this->player = Player(this->wad_data.GetThings()[0]);
    this->player.SetXPos(this->renderer.RemapX(this->player.GetXPos()));
    this->player.SetYPos(this->renderer.RemapY(this->player.GetYPos()));
}

void CapulusEngine::draw() {
    this->renderer.DrawVertexes();
    this->renderer.DrawThings();
    // this->player.Draw();
}