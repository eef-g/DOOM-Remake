#ifndef WAD_DATA_HPP
#define WAD_DATA_HPP
#include "raylib.h"
#include "wad_reader.hpp"
#include "data_types.hpp"



class WADData {
private:
    WADReader reader;
    int map_index;
    std::vector<Vector2> vertexes;
    std::vector<LINEDEF> linedefs;
    std::vector<NODE> nodes;
    std::vector<SUBSECTOR> ssectors;
    std::vector<SEG> segs;
    std::vector<THING> things;


    int GetLumpIndex(std::string lump_name);
    std::vector<Vector2> ReadVertexLump();
    std::vector<LINEDEF> ReadLinedefLump();
    std::vector<NODE> ReadNodeLump();
    std::vector<SUBSECTOR> ReadSubsectorLump();
    std::vector<SEG> ReadSegLump();
    std::vector<THING> ReadThingLump();

public:
    WADData() {};
    WADData(std::string path, std::string map_name);
    std::vector<Vector2> GetVertexes() { return this->vertexes; };
    std::vector<LINEDEF> GetLinedefs() { return this->linedefs; };
    std::vector<THING> GetThings() { return this->things; };
};

#endif
