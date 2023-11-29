#ifndef CAPULUS_ENGINE_HPP
#define CAPULUS_ENGINE_HPP
#include "../wad_classes/wad_data.hpp"
#include "map_renderer.hpp"
#include "player.hpp"
#include "../settings.hpp"
#include "debug_menu.hpp"

class CapulusEngine {
private:
    std::string wad_path;
    std::string map_name;
    WADData wad_data;
    MapRenderer renderer;    
    Player player;

    void init();
public:

    DebugMenu debugMenu;
    int GetScreenHeight() { return WIN_H; }
    int GetScreenWidth() { return WIN_W; }
    CapulusEngine() {};
    CapulusEngine(std::string wad_path);
    void draw();
};

#endif