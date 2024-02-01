#ifndef MODEL_HPP
#define MODEL_HPP

#include <wad/wad_file.hpp>
#include "settings.hpp"

namespace dm {
    class Model{
    private:
        struct gs{
            int screen_width;
            int screen_height;
            int max_fps;
        } settings;
        wad::WADFile *wad = nullptr;


    public:
        void SelectWad(std::string wadName);
        void SelectMap(std::string mapName);
        Model();
        ~Model() { delete this->wad; };

        // Getters
        int GetScreenWidth() { return this->settings.screen_width; };
        int GetScreenHeight() { return this->settings.screen_height; };
        int GetMaxFPS() { return this->settings.max_fps; };
        std::vector<wad::VERTEX> GetMapVertexes() { return this->wad->GetVertexes(); };
        std::vector<wad::LINEDEF> GetMapLinedefs() { return this->wad->GetLinedefs(); };
    };
}
#endif