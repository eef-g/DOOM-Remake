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
    // Now parse info from the map we're reading

    // Parse vertexes
    this->vertexes = this->ReadVertexLump();
    // Parse linedefs
    this->linedefs = this->ReadLinedefLump();
    // Parse nodes
    this->nodes = this->ReadNodeLump();
    // Parse Subsectors
    this->ssectors = this->ReadSubsectorLump();
    // Parse Sectors
    this->sectors = this->ReadSectorLump();
    // Parse Things
    this->things = this->ReadThingLump();
}


int WADData::GetLumpIndex(std::string lump_name) {
    for(int i=0;i<this->reader.dir.lumps.size();i++) {
        if(this->reader.dir.lumps.at(i).lump_name == lump_name) {
            return i;
        }
    }
    return -1;
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

std::vector<SECTOR> WADData::ReadSectorLump() {
    int lump_index = this->map_index + LUMP_INDICIES::SECTORS;
    int num_bytes = 12;
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

