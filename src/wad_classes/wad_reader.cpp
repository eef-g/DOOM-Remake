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

int32_t WADReader::BytesToInt(std::vector<unsigned char> bytes) {
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


THING WADReader::ReadThing(int offset) {
    THING output;
    output.x_pos = LittleEndianToInt(this->ReadBytes(offset, 2));
    output.y_pos = LittleEndianToInt(this->ReadBytes(offset + 2, 2));
    output.angle = LittleEndianToInt(this->ReadBytes(offset + 4, 2));
    output.thing_type = LittleEndianToInt(this->ReadBytes(offset + 6, 2));
    output.flags = LittleEndianToInt(this->ReadBytes(offset + 8, 2));
    return output;
}

LINEDEF WADReader::ReadLinedef(int offset) {
    LINEDEF output;
    output.start_vertex = LittleEndianToInt(this->ReadBytes(offset, 2));
    output.end_vertex = LittleEndianToInt(this->ReadBytes(offset + 2, 2));
    output.flags = LittleEndianToInt(this->ReadBytes(offset + 4, 2));
    output.special_type = LittleEndianToInt(this->ReadBytes(offset + 6, 2));
    output.sector_tag = LittleEndianToInt(this->ReadBytes(offset + 8, 2));
    output.front_sidedef = LittleEndianToInt(this->ReadBytes(offset + 10, 2));
    output.back_sidedef = LittleEndianToInt(this->ReadBytes(offset + 12, 2));
    return output;
}

SIDEDEF WADReader::ReadSidedef(int offset) {
    SIDEDEF output;
    output.x_offset = LittleEndianToInt(this->ReadBytes(offset, 2));
    output.y_offset = LittleEndianToInt(this->ReadBytes(offset + 2, 2));
    std::string upper_texture = BytesToString(this->ReadBytes(offset + 4, 8));
    std::string lower_texture = BytesToString(this->ReadBytes(offset + 12, 8));
    std::string middle_texture = BytesToString(this->ReadBytes(offset + 20, 8));
    // Convert the upper_texture, lower_texture, and middle_texture to a usable 8 character array of chars
    for (int i = 0; i < 8; i++) {
        output.upper_texture[i] = upper_texture[i];
        output.lower_texture[i] = lower_texture[i];
        output.middle_texture[i] = middle_texture[i];
    }
    output.sector_id = LittleEndianToInt(this->ReadBytes(offset + 28, 2));
    return output;
}

Vector2 WADReader::ReadVertex(int offset) {
    int16_t x = LittleEndianToInt(this->ReadBytes(offset, 2));
    int16_t y = LittleEndianToInt(this->ReadBytes(offset + 2, 2));

    Vector2 output = {x, y}; 
    return output;
}

SEG WADReader::ReadSeg(int offset) {
    SEG output;
    output.start_vertex_id = LittleEndianToInt(this->ReadBytes(offset, 2));
    output.end_vertex_id = LittleEndianToInt(this->ReadBytes(offset + 2, 2));
    output.angle = LittleEndianToInt(this->ReadBytes(offset + 4, 2));
    output.linedef_id = LittleEndianToInt(this->ReadBytes(offset + 6, 2));
    output.direction = LittleEndianToInt(this->ReadBytes(offset + 8, 2));
    output.offset = LittleEndianToInt(this->ReadBytes(offset + 10, 2));
    return output;
}

SUBSECTOR WADReader::ReadSubsector(int offset) {
    SUBSECTOR output;
    output.seg_count = LittleEndianToInt(this->ReadBytes(offset, 2));
    output.first_seg_id = LittleEndianToInt(this->ReadBytes(offset + 2, 2));
    return output;
}

BBox WADReader::ReadBBox(int offset) {
    BBox output;
    output.top = LittleEndianToInt(this->ReadBytes(offset, 2));
    output.bottom = LittleEndianToInt(this->ReadBytes(offset + 2, 2));
    output.left = LittleEndianToInt(this->ReadBytes(offset + 4, 2));
    output.right = LittleEndianToInt(this->ReadBytes(offset + 6, 2));
    return output;
}

NODE WADReader::ReadNode(int offset) {
    NODE output;
    output.x_partition = LittleEndianToInt(this->ReadBytes(offset, 2));
    output.y_partition = LittleEndianToInt(this->ReadBytes(offset + 2, 2));
    output.dx_partition = LittleEndianToInt(this->ReadBytes(offset + 4, 2));
    output.dy_partition = LittleEndianToInt(this->ReadBytes(offset + 6, 2));
    output.left_bbox = this->ReadBBox(offset + 8);
    output.right_bbox = this->ReadBBox(offset + 16);
    output.front_child_id = LittleEndianToInt(this->ReadBytes(offset + 24, 2));
    output.back_child_id = LittleEndianToInt(this->ReadBytes(offset + 26, 2));
    return output;
}

SECTOR WADReader::ReadSector(int offset) {
    SECTOR output;
    output.floor_height = LittleEndianToInt(this->ReadBytes(offset, 2));
    output.ceiling_height = LittleEndianToInt(this->ReadBytes(offset + 2, 2));
    std::string floor_texture = BytesToString(this->ReadBytes(offset + 4, 8));
    std::string ceiling_texture = BytesToString(this->ReadBytes(offset + 12, 8));
    for (int i = 0; i < 8; i++) {
        output.floor_texture[i] = floor_texture[i];
        output.ceiling_texture[i] = ceiling_texture[i];
    }
    output.light_level = LittleEndianToInt(this->ReadBytes(offset + 20, 2));
    output.special_type = LittleEndianToInt(this->ReadBytes(offset + 22, 2));
    output.sector_tag = LittleEndianToInt(this->ReadBytes(offset + 24, 2));
    return output;
}

REJECT_LUMP WADReader::ReadReject(int offset) {
    REJECT_LUMP output;
    output.num_reject = LittleEndianToInt(this->ReadBytes(offset, 2));
    output.first_reject = LittleEndianToInt(this->ReadBytes(offset + 2, 2));
    return output;
}

BLOCKMAP_LUMP WADReader::ReadBlockmap(int offset) {
    BLOCKMAP_LUMP output;
    output.origin_x = LittleEndianToInt(this->ReadBytes(offset, 2));
    output.origin_y = LittleEndianToInt(this->ReadBytes(offset + 2, 2));
    return output;
}