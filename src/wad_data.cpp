#include "wad_data.hpp"

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
}

int WADData::GetLumpIndex(std::string lump_name) {
    for(int i=0;i<this->reader.dir.lumps.size();i++) {
        if(this->reader.dir.lumps.at(i).lump_name == lump_name) {
            return i;
        }
    }
    return -1;
}

std::vector<char> WADData::ReadLumpBytes(int lump_index, int num_bytes, int header_length) {
    WADLump lump_info = this->reader.dir.lumps.at(lump_index);
    int count = lump_info.lump_size / num_bytes;
    
    std::vector<char> data;
    int offset = 0;
    for(int i = 0; i < count; i++) {
        offset = lump_info.lump_pos + i * num_bytes + header_length;
        char curr_data = this->reader.ReadBytes(offset, 1)[0]; 
        data.push_back(curr_data);
    }
}