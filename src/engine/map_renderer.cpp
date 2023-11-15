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
    return ( max(this->x_min, min(n, this->x_max)) - this->x_min) * 
            (out_max - out_min) / (this->x_max - this->x_min) + out_min;
}

int MapRenderer::RemapY(int n, int out_min, int out_max) {
    int firstChunk = min(n, this->y_max);
    // std::cout << "First chunk done" << std::endl;
    int secondChunk = max(this->y_min, firstChunk);
    // std::cout << "Second chunk done" << std::endl;
    int thirdChunk = WIN_H - secondChunk;
    // std::cout << "Third chunk done" << std::endl;
    int fourthChunk = (out_max - out_min);
    // std::cout << "Fourth chunk done" << std::endl;
    int fifthChunk = (this->y_max - this->y_min) - out_min;
    // std::cout << "Fifth chunk done" << std::endl;
    int sixthChunk = thirdChunk * fifthChunk;
    // std::cout << "Sixth chunk done" << std::endl;
    return sixthChunk;
    // return WIN_H - (max(this->y_min, min(n, this->y_max)) - this->y_min) * 
            // (out_max - out_min) / (this->y_max - this->y_min) - out_min;
}

MapRenderer::MapRenderer(WADData data) {
    this->wad_data = data;
    

    for(auto vertex : this->wad_data.GetVertexes()) {
        int newX = this->RemapX(vertex.x);
        int newY = this->RemapY(vertex.y);
        Vector2 newVertex = {newX, newY};
        this->vertexes.push_back(newVertex);
    }
    // for(auto vertex : this->wad_data.GetVertexes()) {
    //     std::cout << "{ " << static_cast<int>(vertex.x) << " , " << static_cast<int>(vertex.y) << " }" << std::endl;
    // }
}


void MapRenderer::DrawVertexes() {
    for(auto vertex : this->vertexes) {
        DrawCircle(vertex.x, vertex.y, 30.0, WHITE);
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
    this->x_min = sorted_x.at(0);
    this->x_max = sorted_x.at(sorted_x.size() - 1);
    this->y_min = sorted_y.at(0);
    this->y_max = sorted_y.at(sorted_y.size() - 1);
}