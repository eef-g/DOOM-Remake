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

void MapRenderer::DrawThings() {
    // Go through each thing & find out the type it is. Based off of that, change the color
    for(auto thing: this->wad_data.GetThings()) {
        int x = this->RemapX(thing.x_pos);
        int y = this->RemapY(thing.y_pos);
        switch(getThingType(thing.thing_type)) {
            case ENEMY:
                DrawCircle(x, y, 5.0, RED);
                break;
            case WEAPON:
                DrawCircle(x, y, 5.0, GRAY);
                break;
            case AMMO:
                DrawCircle(x, y, 5.0, DARKGRAY);
                break;
            case ARTIFACT:
                DrawCircle(x, y, 5.0, DARKBLUE);
                break;
            case POWERUP:
                DrawCircle(x, y, 5.0, GREEN);
                break;
            case OBSTACLE:
                DrawCircle(x, y, 5.0, BROWN);
                break;
            case DECOR:
                DrawCircle(x, y, 5.0, LIGHTGRAY);
                break;
            case OTHER:
                DrawCircle(x, y, 5.0, DARKGREEN);
                break;
            default:
                DrawCircle(x, y, 5.0, DARKGREEN);
                break;
        }
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