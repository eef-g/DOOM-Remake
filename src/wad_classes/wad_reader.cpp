#include "wad_reader.hpp"
#include <iomanip>

// Helper Functions
std::string BytesToString(std::vector<unsigned char> bytes) {
    std::string output(bytes.begin(), bytes.end());
    return output;
}


void PrintIntToHex(int32_t num) {
    std::cout << "0x" << std::hex << num;
}


void PrintCharsToHex(std::vector<unsigned char> bytes) {
    std::cout << "[ ";
    for (unsigned char byte : bytes) {
        std::cout << "0x" << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << " ";
    }
    std::cout << "]" << std::endl;
}


// TODO: Fix conversion from little endian to normal int
int32_t WADReader::BytesToInt(std::vector<unsigned char> bytes) {
    // std::cout << "[ ";
    // for (unsigned char byte : bytes) {
    //     std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte) << " ";
    // }
    // std::cout << " ]" << std::endl;
    int32_t result = (bytes[3]) << 24 | static_cast<uint32_t>(bytes[2]) << 16 | static_cast<uint32_t>(bytes[1]) << 8 | static_cast<uint32_t>(bytes[0]);
    return result;
}


int16_t LittleEndianToInt(std::vector<unsigned char> bytes) {
    // Split the vector into two different hex values
    int16_t first_hex = static_cast<uint16_t>(bytes[1]) << 8| static_cast<uint16_t>(bytes[0]);
    int16_t second_hex = static_cast<uint16_t>(bytes[3]) << 8 | static_cast<uint16_t>(bytes[2]);
    // For whatever reason, I don't know why, but the second_hex is the issue and it does us NO GOOD AT ALL.
    // So, we just ignore it and go on our merry way :)
    // I kept it in the code here in case it turns out I actually need it, but I'm not sure about it yet.
    return first_hex;
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
    
    // Initialize the WAD Info
    this->header = this->ReadHeader();

    this->dir = this->ReadDir();
    int vertex_count = 0;
}


std::vector<unsigned char> WADReader::ReadBytes(int offset, int num_bytes) {
    if (offset < 0 || offset + num_bytes > this->buffer.size()) { 
        exit(0);
    }

    std::vector<unsigned char> result(buffer.begin() + offset, buffer.begin() + offset + num_bytes);
    return result;
}


WADHeader WADReader::ReadHeader() {
    WADHeader header;
    header.wad_type = BytesToString(this->ReadBytes(0, 4));
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
        std::string name = BytesToString(this->ReadBytes(offset + 8, 8));
        lump.lump_name = trim(name);
        dir.lumps.push_back(lump);
    }
    return dir;
}

Vector2 WADReader::ReadVertex(int offset) {
    int16_t x = LittleEndianToInt(this->ReadBytes(offset, 2));
    int16_t y = LittleEndianToInt(this->ReadBytes(offset + 2, 2));

    Vector2 output = {x, y}; 
    return output;
}