#ifndef DATA_TYPES_HPP
#define DATA_TYPES_HPP

#include <iostream>

enum LUMP_INDICIES {
    THINGS = 1, LINEDEFS = 2, SIDEDEFS = 3, VERTEXES = 4, SEGS = 5,
    SSECTORS = 6, NODES = 7, SECTORS = 8, REJECT = 9, BLOCKMAP = 10,
};

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
    // 12 bytes
    int16_t start_vertex_id;
    int16_t end_vertex_id;
    int16_t angle;
    int16_t linedef_id;
    int16_t direction;
    int16_t offset;
};

struct THING {
    // 10 bytes
    int16_t x_pos;
    int16_t y_pos;
    int16_t angle;
    int16_t thing_type;
    int16_t flags;
};

struct SUBSECTOR {
    // 4 bytes
    int16_t seg_count;
    int16_t first_seg_id;
};

#endif