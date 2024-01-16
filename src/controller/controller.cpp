#include "controller.hpp"

namespace dc {
    Controller::Controller() {
        this->model = dm::Model();
    }

    void Controller::SelectMap(std::string mapName) {
        this->model.SelectMap(mapName);
    }
}