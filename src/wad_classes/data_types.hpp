#ifndef DATA_TYPES_HPP
#define DATA_TYPES_HPP

#include <iostream>
#include <vector>
#include <algorithm>

enum LUMP_INDICIES {
    THINGS = 1, LINEDEFS = 2, SIDEDEFS = 3, VERTEXES = 4, SEGS = 5,
    SSECTORS = 6, NODES = 7, SECTORS = 8, REJECT = 9, BLOCKMAP = 10,
};

struct THING {
    // 10 bytes
    int16_t x_pos;
    int16_t y_pos;
    int16_t angle;
    int16_t thing_type;
    int16_t flags;
};

enum THING_TYPE {
    ENEMY = 1, WEAPON = 2, AMMO = 3, ARTIFACT = 4,
    POWERUP = 5, KEY = 6, OBSTACLE = 7, DECOR = 8,
    OTHER = 9,  
};

struct ThingType {
    THING_TYPE type;
    std::vector<int> thing_numbers;
};

std::vector<ThingType> thing_types = {
    {ENEMY, {68, 64, 3003, 3005, 72, 16, 3002, 65, 69, 3001, 3006, 67, 66, 71, 9, 58, 7, 84, 3004}},
    {WEAPON, {2006, 2002, 2005, 2004, 2003, 2001, 82}},
    {AMMO, {2008, 2048, 2046, 2049, 2007, 2047, 17, 2010}},
    {ARTIFACT, {2015, 2023, 2026, 2014, 2022, 2045, 83, 2024, 2013}},
    {POWERUP, {2018, 8, 2012, 2019, 2025, 2011}},
    {KEY, {5, 40, 13, 38, 6, 39}},
    {OBSTACLE, {47, 70, 43, 35, 41, 2035, 28, 42, 2028, 53, 52, 78, 75, 77, 76, 50, 74, 73, 51, 49, 25, 54, 29, 55, 56, 31, 36, 57, 33, 37, 86, 27, 44, 45, 30, 46, 32, 48, 85, 26}},
    {DECOR, {10, 12, 34, 22, 21, 18, 19, 20, 23, 15, 62, 60, 59, 61, 63, 79, 80, 24, 81}},
    {OTHER, {11, 89, 1, 2, 3, 4, 88, 87, 14}}
};

THING_TYPE getThingType(int thing_type) {
    for (const ThingType& thingType : thing_types) {
        if (std::find(thingType.thing_numbers.begin(), thingType.thing_numbers.end(), thing_type) != thingType.thing_numbers.end()) {
            return thingType.type;
        }
    }
    return OTHER;
}


struct LINEDEF {
    // 14 bytes total
    int16_t start_vertex;
    int16_t end_vertex;
    int16_t flags;
    int16_t special_type;
    int16_t sector_tag;
    int16_t front_sidedef;
    int16_t back_sidedef;
};

struct SIDEDEF {
    // 30 bytes total
    int16_t x_offset;
    int16_t y_offset;
    char upper_texture[8];
    char lower_texture[8];
    char middle_texture[8];
    int16_t sector_id;
};

// VERTEX struct is just a Vector2, no need to make a custom one for this struct

struct SEG {
    // 12 bytes total
    int16_t start_vertex_id;
    int16_t end_vertex_id;
    int16_t angle;
    int16_t linedef_id;
    int16_t direction;
    int16_t offset;
};

struct SUBSECTOR {
    // 4 bytes
    int16_t seg_count;
    int16_t first_seg_id;
};

struct BBox {
    // 8 bytes total
    int16_t top;
    int16_t bottom;
    int16_t left;
    int16_t right;
};

struct NODE {
    // 28 bytes total
    int16_t x_partition;
    int16_t y_partition;
    int16_t dx_partition;
    int16_t dy_partition;
    BBox left_bbox;
    BBox right_bbox;
    int16_t front_child_id;
    int16_t back_child_id;
};

struct SECTOR {
    // 26 bytes total
    int16_t floor_height;
    int16_t ceiling_height;
    char floor_texture[8];
    char ceiling_texture[8];
    int16_t light_level;
    int16_t special_type;
    int16_t sector_tag;
};

struct REJECT_LUMP {
    // 4 bytes total
    int16_t num_reject;
    int16_t first_reject;
};

struct BLOCKMAP_LUMP {
    // 4 bytes total
    int16_t origin_x;
    int16_t origin_y;
};


#endif