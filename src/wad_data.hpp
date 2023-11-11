#ifndef WAD_DATA_HPP
#define WAD_DATA_HPP
#include "wad_reader.hpp"

const struct LUMP_INDICIES {
    int THINGS = 1; int LINEDEFFS = 2; int SIDEDEFS = 3; int VERTEXES = 4; int SEGS = 5;
    int SSSECTORS = 6; int NODES = 7; int SECTORS = 8; int REJECT = 9; int BLOCKMAP = 10;
};

enum ReaderFunction {
    VERTEX,
};

class WADData {
private:
    WADReader reader;
    int map_index;    

    int GetLumpIndex(std::string lump_name);
    std::vector<char> ReadLumpBytes(int lump_index, int num_bytes, int header_length);
public:
    WADData() {};
    WADData(std::string path, std::string map_name);
};

#endif