#include "capulus_engine.hpp"

CapulusEngine::CapulusEngine(std::string wad_path) {
    this->wad_path = wad_path;
    this->map_name = "E1M1";
    this->init();
}

void CapulusEngine::init() {
    this->wad_data = WADData(this->wad_path, this->map_name);
}