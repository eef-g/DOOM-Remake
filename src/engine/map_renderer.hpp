#ifndef MAP_RENDERER_HPP
#define MAP_RENDERER_HPP
#include "../settings.hpp"
#include "../wad_classes/wad_data.hpp"
#include <algorithm>
#include <vector>

class MapRenderer {
private:
    WADData wad_data;
    int x_min, x_max, y_min, y_max;
    std::vector<Vector2> vertexes;

    
    int RemapX(int n, int out_min=30, int out_max=WIN_W-30);
    int RemapY(int n, int out_min=30, int out_max=WIN_H-30);
public:
    MapRenderer() {};
    MapRenderer(WADData data);

    void DrawVertexes();
    void GetMapBounds();
};

#endif