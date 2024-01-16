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
        wad::WADFile wad;


    public:
        void SelectMap(std::string mapName);
        Model();

        // Getters
        int GetScreenWidth() { return this->settings.screen_width; };
        int GetScreenHeight() { return this->settings.screen_height; };
        int GetMaxFPS() { return this->settings.max_fps; };
    };
}
#endif