#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "../model/model.hpp"
#include <vector>
#include <wad/data_types.hpp>

namespace dc {
    class Controller {
    private:
        dm::Model *model = nullptr;

        // Functions & Variables for 2D map used in MapTest and MiniMap
        int max(int a, int b) { return (a > b) ? a : b; };
        int min(int a, int b){ return (a < b) ? a : b;};
        int Remap2DX(int n, int out_min=30, int out_max=WIN_H-30);
        int Remap2DY(int n, int out_min=30, int out_max=WIN_H-30);
        int x_min, x_max, y_min, y_max;
        void GetMapBounds();

    public:
        Controller();
        ~Controller() { delete this->model; };

        // Getters
        int GetScreenWidth() { return this->model->GetScreenHeight(); };
        int GetScreenHeight() { return this->model->GetScreenWidth(); };
        int GetMaxFPS() { return this->model->GetMaxFPS(); };

        // Map-based data
        void SelectMap(std::string mapName); 
        std::vector<wad::VERTEX> map_vertexes_2D;
        std::vector<wad::LINEDEF> map_linedefs_2D;
    };
}

#endif