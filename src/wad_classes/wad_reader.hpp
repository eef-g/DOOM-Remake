#ifndef WAD_READER_HPP
#define WAD_READER_HPP

#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <raylib-cpp.hpp>

#include "data_types.hpp"

struct WADHeader {
    std::string wad_type;
    int lump_count;
    int init_offset;
};

struct WADLump {
    int lump_pos;
    int lump_size;
    std::string lump_name;
};

struct WADDir {
    std::vector<WADLump> lumps;
};


class WADReader {
private:
    std::string wad_path;
    std::vector<char> buffer;

    WADHeader ReadHeader();
    WADDir ReadDir();

public:
    WADHeader header;
    WADDir dir;
    WADReader() {};
    WADReader(std::string wad_path);
    
    int32_t BytesToInt(std::vector<unsigned char> bytes);

    THING ReadThing(int offset);
    LINEDEF ReadLinedef(int offset);
    SIDEDEF ReadSidedef(int offset);
    Vector2 ReadVertex(int offset);
    SEG ReadSeg(int offset);
    SUBSECTOR ReadSubsector(int offset);
    BBox ReadBBox(int offset);
    NODE ReadNode(int offset);
    SECTOR ReadSector(int offset);
    REJECT ReadReject(int offset);
    BLOCKMAP ReadBlockmap(int offset);

    std::vector<unsigned char> ReadBytes(int offset, int num_bytes);
};
#endif