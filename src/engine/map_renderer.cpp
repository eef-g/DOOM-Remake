#include "map_renderer.hpp"

// Helper functions
int max(int a, int b) {
    if(a > b) { return a; }
    else { return b;}
}

int min(int a, int b) {
    if(a < b) { return a; }
    else { return b; }
}

int MapRenderer::RemapX(int n, int out_min, int out_max) {
    int remapped = static_cast<int>((max(this->x_min, min(n, this->x_max)) - this->x_min) * 
                (static_cast<float>(out_max - out_min) / (this->x_max - this->x_min)) + out_min);

    // Clamp the remapped value to be within the window
    remapped = max(out_min, min(remapped, out_max));
}

int MapRenderer::RemapY(int n, int out_min, int out_max) {
    int remapped = static_cast<int>((max(this->y_min, min(n, this->y_max)) - this->y_min) * 
                (static_cast<float>(out_max - out_min) / (this->y_max - this->y_min)) - out_min);

    // Invert the y-coordinate to match the screen's coordinate system
    remapped = WIN_H - remapped;

    return remapped;
}

MapRenderer::MapRenderer(WADData data) {
    this->wad_data = data;
    this->GetMapBounds();

    for(auto vertex : this->wad_data.GetVertexes()) {
        int newX = this->RemapX(vertex.x);
        int newY = this->RemapY(vertex.y);
        Vector2 newVertex = {newX, newY};
        this->vertexes.push_back(newVertex);
    }

    this->lines = this->wad_data.GetLinedefs();
    // for(auto line : this->lines) {
    //     std::cout << "[ Start: " << line.start_vertex << " | End: " << line.end_vertex << " ]" << std::endl;
    // }
}


void MapRenderer::DrawVertexes() {
    // Draw all the vertexes
    for(auto vertex : this->vertexes) {
        DrawCircle(vertex.x, vertex.y, 2.5, WHITE);
    }
    // Draw all the lines
    for(auto line : this->lines) {
        DrawLineV(this->vertexes[line.start_vertex], this->vertexes[line.end_vertex], WHITE);
    }
}

void MapRenderer::GetMapBounds() {
    std::vector<int> sorted_x, sorted_y;
    int x_min, x_max, y_min, y_max;
    for(auto vertex : this->wad_data.GetVertexes()) {
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