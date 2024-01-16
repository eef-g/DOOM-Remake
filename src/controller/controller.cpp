#include "controller.hpp"

namespace dc {
    Controller::Controller() {
        this->model = new dm::Model();
    }

    void Controller::SelectMap(std::string mapName) {
        this->model->SelectMap(mapName);
    }
}