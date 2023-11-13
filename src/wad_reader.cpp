#include "wad_reader.hpp"


// Helper Functions

int WADReader::BytesToInt(const std::string& bytes) {
    int result = 0;
    for (int i = 0; i < bytes.size(); ++i) {
        result |= (static_cast<unsigned char>(bytes[i]) << (i * 8));
    }
    return result;
}

// Let's us convert the bytes into a usable string value
std::string trim(std::string& str) {
    int end_index = 0;
    for(char c: str) {
        if(static_cast<int>(c) == 0) {
            break;
        }
        end_index++;
    }
    if(end_index == str.size()) { return str; }
    else { return str.substr(0, end_index); }
}

void PrintHeader(WADHeader header) {
    std::cout << "+---------------------------------+" << std::endl;
    std::cout << "| WAD Filetype: " << header.wad_type << std::endl;
    std::cout << "| Lump Count: " << header.lump_count << std::endl;
    std::cout << "| Initial Offset: " << header.init_offset << std::endl;
    std::cout << "+---------------------------------+" << std::endl;
}

void PrintLump(WADLump lump) {
    std::cout << "+---------------------------------+" << std::endl;
    std::cout << "| Lump Position: " << lump.lump_pos << std::endl;
    std::cout << "| Lump Size: " << lump.lump_size << std::endl;
    std::cout << "| Lump Name: " << lump.lump_name << std::endl;
    std::cout << "+---------------------------------+\n" << std::endl;
}




// WADReader Functions

WADReader::WADReader(std::string wad_path) {
    this->wad_path = wad_path;

    std::ifstream file(wad_path, std::ios::binary | std::ios::ate);
    if (file) {
        std::streamsize size = file.tellg();
        file.seekg(0, std::ios::beg);

        buffer.resize(size);
        if(!file.read(buffer.data(), size)) {
            // Handle error
        }
    } else {
        std::cout << "No file found!\n";
        exit(0);   
    }
    std::cout << "WAD Reader created\n";
    
    // Initialize the WAD Info
    this->header = this->ReadHeader();
    PrintHeader(this->header);

    this->dir = this->ReadDir();
    for(const auto& lump : this->dir.lumps) {
        if(lump.lump_name == "VERTEXES") {
            PrintLump(lump);
        }
    }
}


std::string WADReader::ReadBytes(int offset, int num_bytes) {
    if (offset < 0 || offset + num_bytes > this->buffer.size()) { 
        exit(0);
    }

    std::string result(buffer.begin() + offset, buffer.begin() + offset + num_bytes);
    return result;
}


WADHeader WADReader::ReadHeader() {
    WADHeader header;
    header.wad_type = this->ReadBytes(0, 4);
    header.lump_count = this->BytesToInt(this->ReadBytes(4, 4));
    header.init_offset = this->BytesToInt(this->ReadBytes(8, 4));
    return header;
}


WADDir WADReader::ReadDir() {
    WADDir dir;
    for(int i = 0; i < this->header.lump_count;i++) {
        int offset = this->header.init_offset + i * 16;
        WADLump lump;
        lump.lump_pos = this->BytesToInt(this->ReadBytes(offset, 4));
        lump.lump_size = this->BytesToInt(this->ReadBytes(offset + 4, 4));
        std::string name = this->ReadBytes(offset + 8, 8);
        lump.lump_name = trim(name);
        dir.lumps.push_back(lump);
    }
    return dir;
}

Vector2 WADReader::ReadVertex(int offset) {
    int x = this->BytesToInt(this->ReadBytes(offset, 2));
    int y = this->BytesToInt(this->ReadBytes(offset + 2, 2));
    Vector2 output = {x, y};
    return output;
}

void WADReader::PrintLumpInfo(WADLump lump) {
  std::cout << "+---------------------+" << std::endl;
  std::cout << "| Lump Name: " << lump.lump_name << std::endl;
  std::cout << "| Lump Size: " << lump.lump_size << std::endl;
  std::cout << "| Lump Position: " << lump.lump_pos << std::endl;
  std::cout << "+---------------------+" << std::endl;
}
