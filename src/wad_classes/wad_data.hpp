#ifndef WAD_DATA_HPP
#define WAD_DATA_HPP
#include "raylib.h"
#include "wad_reader.hpp"

enum LUMP_INDICIES {
    THINGS = 1, LINEDEFFS = 2, SIDEDEFS = 3, VERTEXES = 4, SEGS = 5,
    SSSECTORS = 6, NODES = 7, SECTORS = 8, REJECT = 9, BLOCKMAP = 10,
};


class WADData {
private:
    WADReader reader;
    int map_index;
    std::vector<Vector2> vertexes;
    std::vector<LINEDEF> linedefs;

    int GetLumpIndex(std::string lump_name);
    std::vector<Vector2> ReadVertexLump();
    std::vector<LINEDEF> ReadLinedefLump();

public:
    WADData() {};
    WADData(std::string path, std::string map_name);
    std::vector<Vector2> GetVertexes() { return this->vertexes; };
    std::vector<LINEDEF> GetLinedefs() { return this->linedefs; };
};

#endif
