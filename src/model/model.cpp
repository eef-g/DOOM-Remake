#include "model.hpp"
namespace dm {
    Model::Model() {
        this->settings.screen_height = WIN_H;
        this->settings.screen_width = WIN_W;
        this->settings.max_fps = FPS;
        this->wad = new wad::WADFile();
        this->SelectWad("doom1");
    }


    void Model::SelectWad(std::string wadName) {
        std::cout << "Loading Wad: " << wadName << std::endl;
        std::string wad_path = "resources/wads/" + wadName + ".wad";
        this->wad->ReadWad(wad_path);
        std::cout << "Wad loaded" << std::endl;
    }
    void Model::SelectMap(std::string mapName) {
        this->wad->ReadMap(mapName);
    }

    wad::VERTEX Model::GetPlayerStart() {
        for (auto thing : this->wad->GetThings()) {
            if (thing.thing_type == 1) {
                return {thing.x_pos, thing.y_pos};
            }
        }
    }
}