#ifndef CAPULUS_ENGINE_HPP
#define CAPULUS_ENGINE_HPP
#include "wad_data.hpp"

class CapulusEngine {
private:
    std::string wad_path;
    std::string map_name;
    WADData wad_data;
    

    void init();
public:
    CapulusEngine(std::string wad_path);
};

#endif