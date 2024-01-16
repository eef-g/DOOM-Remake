#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "../model/model.hpp"

namespace dc {
    class Controller {
    private:
        dm::Model model;
    public:
        Controller();

        // Getters
        int GetScreenWidth() { return this->model.GetScreenHeight(); };
        int GetScreenHeight() { return this->model.GetScreenWidth(); };
        int GetMaxFPS() { return this->model.GetMaxFPS(); };

        void SelectMap(std::string mapName);
    };
}

#endif