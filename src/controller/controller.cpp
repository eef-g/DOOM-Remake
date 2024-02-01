#include "controller.hpp"

namespace dc {
    Controller::Controller() {
        this->model = new dm::Model();
    }

    void Controller::SelectMap(std::string mapName) {
        std::cout << "Loading Map: " << mapName << std::endl;
        this->model->SelectMap(mapName);
        std::cout << "Map loaded" << std::endl;

        std::cout << "Getting map bounds" << std::endl;
        this->GetMapBounds();
        std::cout << "Remapping map vertexes" << std::endl;
        for (auto vertex: this->model->GetMapVertexes()) {
            std::cout << "Remapping vertex: (" << vertex.x << ", " << vertex.y << ")" << std::endl;
            wad::VERTEX vertex_2D;
            vertex_2D.x = Remap2DX(vertex.x);
            vertex_2D.y = Remap2DY(vertex.y);
            std::cout << "Vertex remapped to: (" << vertex_2D.x << ", " << vertex_2D.y << ")" << std::endl;
            this->map_vertexes_2D.push_back(vertex_2D);
        }
        std::cout << "Getting  map linedefs" << std::endl;
        this->map_linedefs_2D = this->model->GetMapLinedefs();
    }


    void Controller::GetMapBounds() {
        std::vector<int> sorted_x, sorted_y;
        int x_min, x_max, y_min, y_max;
        for(auto vertex : this->model->GetMapVertexes()) {
            sorted_x.push_back(vertex.x);
            sorted_y.push_back(vertex.y);
        }
        std::sort(sorted_x.begin(), sorted_x.end());
        std::sort(sorted_y.begin(), sorted_y.end());
        this->x_min = sorted_x.front();
        this->x_max = sorted_x.back();
        this->y_min = sorted_y.front();
        this->y_max = sorted_y.back();
    }

    int Controller::Remap2DX(int n, int out_min, int out_max) {
        int remapped = static_cast<int>((max(this->x_min, min(n, this->x_max)) - this->x_min) * 
                (static_cast<float>(out_max - out_min) / (this->x_max - this->x_min)) + out_min);
        // Clamp the remapped value to be within the window
        remapped = max(out_min, min(remapped, out_max));
        return remapped;
    }

    int Controller::Remap2DY(int n, int out_min, int out_max) {
        int remapped = static_cast<int>((max(this->y_min, min(n, this->y_max)) - this->y_min) * 
                (static_cast<float>(out_max - out_min) / (this->y_max - this->y_min)) - out_min);
        // Invert the y-coordinate to match the screen's coordinate system
        remapped = WIN_H - remapped;
        return remapped;
    }
}