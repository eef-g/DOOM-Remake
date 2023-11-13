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
    std::cout << "Lump index of map ['" << map_name << "']: " << this->map_index << std::endl;
    // Parse vertexes
    this->vertexes = this->ReadVertexLump();
    // for(auto vertex : this->vertexes) {
    //   std::cout << "{ " << vertex.x << " , " << vertex.y << " }" << std::endl; 
    // }
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
