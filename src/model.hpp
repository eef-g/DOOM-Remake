#ifndef MODEL_HPP
#define MODEL_HPP

// #include <wad/wad_file.hpp>
#include <raylib.h>
#include "settings.hpp"

namespace doom {
    class Model{
    private:
        int screenWidth;
        int screenHeight;

    public:
        Model();
        void runGame();
    };
}
#endif