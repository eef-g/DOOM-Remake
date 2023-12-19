#ifndef WAD_DATA_HPP
#define WAD_DATA_HPP
#include "raylib.h"
#include "wad_reader.hpp"
#include "data_types.hpp"


class WADData {
private:
    WADReader reader;
    int map_index;
    // Lump Data
    std::vector<THING> things;
    std::vector<LINEDEF> linedefs;
    std::vector<SIDEDEF> sidedefs;
    std::vector<Vector2> vertexes;
    std::vector<SEG> segs;
    std::vector<SUBSECTOR> ssectors;
    std::vector<NODE> nodes;
    std::vector<SECTOR> sectors;
    std::vector<REJECT> rejects;
    std::vector<BLOCKMAP> blockmaps;

    // Lump reading
    int GetLumpIndex(std::string lump_name);
    std::vector<THING> ReadThingLump();
    std::vector<LINEDEF> ReadLinedefLump();
    std::vector<SIDEDEF> ReadSidedefLump();
    std::vector<Vector2> ReadVertexLump();
    std::vector<SEG> ReadSegLump();
    std::vector<SUBSECTOR> ReadSubsectorLump();
    std::vector<NODE> ReadNodeLump();
    std::vector<SECTOR> ReadSectorLump();
    std::vector<REJECT> ReadRejectLump();
    std::vector<BLOCKMAP> ReadBlockmapLump();

public:
    WADData() {};
    WADData(std::string path, std::string map_name);
    std::vector<Vector2> GetVertexes() { return this->vertexes; };
    std::vector<LINEDEF> GetLinedefs() { return this->linedefs; };
    std::vector<THING> GetThings() { return this->things; };
    std::vector<SIDEDEF> GetSidedefs() { return this->sidedefs; };
    std::vector<SEG> GetSegs() { return this->segs; };
    std::vector<SUBSECTOR> GetSubsectors() { return this->ssectors; };
    std::vector<NODE> GetNodes() { return this->nodes; };
    std::vector<SECTOR> GetSectors() { return this->sectors; };
    std::vector<REJECT> GetRejects() { return this->rejects; };
    std::vector<BLOCKMAP> GetBlockmaps() { return this->blockmaps; };
};

#endif
