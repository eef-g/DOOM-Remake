#include "wad_data.hpp"
#include "raylib.h"

// Use this function to check the values of the ASCII characters on the string
void PrintASCIIValues(std::string str) {
    std::cout << "[ ";
    for(char c : str) {
        std::cout << static_cast<int>(c) << ", ";
    }
    std::cout << "]";
}


WADData::WADData(std::string path, std::string map_name) {
    this->reader = WADReader(path);
    this->map_index = this->GetLumpIndex(map_name);
    // Parse lumps related to the map_index
    this->things = this->ReadThingLump();
    this->linedefs = this->ReadLinedefLump();
    this->sidedefs = this->ReadSidedefLump();
    this->vertexes = this->ReadVertexLump();
    this->segs = this->ReadSegLump();
    this->ssectors = this->ReadSubsectorLump();
    this->nodes = this->ReadNodeLump();
    this->sectors = this->ReadSectorLump();
    this->rejects = this->ReadRejectLump();
    this->blockmaps = this->ReadBlockmapLump();
}


int WADData::GetLumpIndex(std::string lump_name) {
    for(int i=0;i<this->reader.dir.lumps.size();i++) {
        if(this->reader.dir.lumps.at(i).lump_name == lump_name) {
            return i;
        }
    }
    return -1;
}

// Lump Parsing Functions

std::vector<THING> WADData::ReadThingLump() {
    int lump_index = this->map_index + LUMP_INDICIES::THINGS;
    int num_bytes = 10;
    int header_length = 0;

    WADLump lump_info = this->reader.dir.lumps[lump_index];
    int count = lump_info.lump_size / num_bytes;
    std::vector<THING> data;
    int offset = 0;
    for(int i = 0; i < count; i++) {
        offset = lump_info.lump_pos + i * num_bytes + header_length;
        THING curr_data = this->reader.ReadThing(offset);
        data.push_back(curr_data);
    }
    return data;
}

std::vector<LINEDEF> WADData::ReadLinedefLump() {
    int lump_index = this->map_index + LUMP_INDICIES::LINEDEFS;
    int num_bytes = 14;
    int header_length = 0;

    WADLump lump_info = this->reader.dir.lumps.at(lump_index);
    int count = lump_info.lump_size / num_bytes;

    std::vector<LINEDEF> data;
    int offset = 0;
    for(int i = 0; i < count; i++) {
        offset = lump_info.lump_pos + i * num_bytes + header_length;
        LINEDEF curr_data = this->reader.ReadLinedef(offset);
        data.push_back(curr_data);
    }
    return data;
}

std::vector<SIDEDEF> WADData::ReadSidedefLump() {
    int lump_index = this->map_index + LUMP_INDICIES::SIDEDEFS;
    int num_bytes = 30;
    int header_length = 0;

    WADLump lump_info = this->reader.dir.lumps.at(lump_index);
    int count = lump_info.lump_size / num_bytes;

    std::vector<SIDEDEF> data;
    int offset = 0;
    for(int i = 0; i < count; i++) {
        offset = lump_info.lump_pos + i * num_bytes + header_length;
        SIDEDEF curr_data = this->reader.ReadSidedef(offset);
        data.push_back(curr_data);
    }
    return data;
}

std::vector<Vector2> WADData::ReadVertexLump() {
    int lump_index = this->map_index + LUMP_INDICIES::VERTEXES;
    int num_bytes = 4;
    int header_length = 0;

    WADLump lump_info = this->reader.dir.lumps.at(lump_index);
    int count = lump_info.lump_size / num_bytes;
    
    std::vector<Vector2> data;
    int offset = 0;
    for(int i = 0; i < count; i++) {
        offset = lump_info.lump_pos + i * num_bytes + header_length;
        Vector2 curr_data = this->reader.ReadVertex(offset);
        data.push_back(curr_data);
    }
    return data;
}

std::vector<SEG> WADData::ReadSegLump() {
    int lump_index = this->map_index + LUMP_INDICIES::SEGS;
    int num_bytes = 12;
    int header_length = 0;

    WADLump lump_info = this->reader.dir.lumps[lump_index];
    int count = lump_info.lump_size / num_bytes;
    std::vector<SEG> data;
    int offset = 0;
    for(int i = 0; i < count; i++) {
        offset = lump_info.lump_pos + i * num_bytes + header_length;
        SEG curr_data = this->reader.ReadSeg(offset);
        data.push_back(curr_data);
    }
    return data;
}


std::vector<SUBSECTOR> WADData::ReadSubsectorLump() {
    int lump_index = this->map_index + LUMP_INDICIES::SSECTORS;
    int num_bytes = 4;
    int header_length = 0;

    WADLump lump_info = this->reader.dir.lumps[lump_index];
    int count = lump_info.lump_size / num_bytes;
    std::vector<SUBSECTOR> data;
    int offset = 0;
    for(int i = 0; i < count; i++) {
        offset = lump_info.lump_pos + i * num_bytes + header_length;
        SUBSECTOR curr_data = this->reader.ReadSubsector(offset);
        data.push_back(curr_data);
    }
    return data;
}


std::vector<NODE> WADData::ReadNodeLump() {
    int lump_index = this->map_index + LUMP_INDICIES::NODES;
    int num_bytes = 28;
    int header_length = 0;

    WADLump lump_info = this->reader.dir.lumps[lump_index];
    int count = lump_info.lump_size / num_bytes;
    std::vector<NODE> data;
    int offset = 0;
    for(int i = 0; i < count; i++) {
        offset = lump_info.lump_pos + i * num_bytes + header_length;
        NODE curr_data = this->reader.ReadNode(offset);
        data.push_back(curr_data);
    }
    return data;
}

std::vector<SECTOR> WADData::ReadSectorLump() {
    int lump_index = this->map_index + LUMP_INDICIES::SECTORS;
    int num_bytes = 26;
    int header_length = 0;

    WADLump lump_info = this->reader.dir.lumps[lump_index];
    int count = lump_info.lump_size / num_bytes;
    std::vector<SECTOR> data;
    int offset = 0;
    for(int i = 0; i < count; i++) {
        offset = lump_info.lump_pos + i * num_bytes + header_length;
        SECTOR curr_data = this->reader.ReadSector(offset);
        data.push_back(curr_data);
    }
    return data;
}

std::vector<REJECT> WADData::ReadRejectLump() {
    int lump_index = this->map_index + LUMP_INDICIES::REJECTS;
    int num_bytes = 4;
    int header_length = 0;

    WADLump lump_info = this->reader.dir.lumps[lump_index];
    int count = lump_info.lump_size / num_bytes;
    std::vector<REJECT> data;
    int offset = 0;
    for(int i = 0; i < count; i++) {
        offset = lump_info.lump_pos + i * num_bytes + header_length;
        REJECT curr_data = this->reader.ReadReject(offset);
        data.push_back(curr_data);
    }
    return data;
}

std::vector<BLOCKMAP> WADData::ReadBlockmapLump() {
    int lump_index = this->map_index + LUMP_INDICIES::BLOCKMAPS;
    int num_bytes = 4;
    int header_length = 0;

    WADLump lump_info = this->reader.dir.lumps[lump_index];
    int count = lump_info.lump_size / num_bytes;
    std::vector<BLOCKMAP> data;
    int offset = 0;
    for(int i = 0; i < count; i++) {
        offset = lump_info.lump_pos + i * num_bytes + header_length;
        BLOCKMAP curr_data = this->reader.ReadBlockmap(offset);
        data.push_back(curr_data);
    }
    return data;
}