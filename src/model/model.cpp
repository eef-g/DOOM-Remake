#include "model.hpp"
namespace dm {
    Model::Model() {
        this->settings.screen_height = WIN_H;
        this->settings.screen_width = WIN_W;
        this->settings.max_fps = FPS;
        this->wad = wad::WADFile();
    }

    void Model::SelectMap(std::string mapName) {
        this->wad.ReadMap(mapName);
    }

}