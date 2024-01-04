cmake_minimum_required(VERSION 3.15)
project(DOOM)
set(This DOOM)


file(GLOB SOURCES 
    "src/*.cpp"
)

file (GLOB HEADERS
    "src/*.hpp"
)

# Assuming you have a target named 'my_target'
add_executable(DOOM ${SOURCES} ${HEADERS})

# Specify the paths to the libraries
set(RAYLIB_LIB "${CMAKE_SOURCE_DIR}/vendor/raylib/src/libraylib.a")
set(WAD_READER_LIB "${CMAKE_SOURCE_DIR}/vendor/wad_reader/libwad.a")

# Link the libraries to your target
target_link_libraries(${This} ${RAYLIB_LIB} ${WAD_READER_LIB})

enable_testing()