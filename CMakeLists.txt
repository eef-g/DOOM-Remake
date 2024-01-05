cmake_minimum_required(VERSION 3.15)

project(DOOM-Remake)
set(This DOOM)

enable_testing()

set(RAYLIB_VERSION 5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET)
if (NOT raylib_FOUND)
    include(FetchContent)
    FetchContent_Declare(
        raylib
        DOWNLOAD_EXTRACT_TIMESTAMP OFF
        URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED)
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
        set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif()
endif()

# Specify the paths to the libraries
set(WAD_READER_LIB "${CMAKE_SOURCE_DIR}/vendor/wad_reader/libwad.a")


file(GLOB SOURCES 
    "src/*.cpp"
)

file (GLOB HEADERS
    "src/*.hpp"
)

include_directories(
    "vendor/wad_reader/src"
)

add_executable(DOOM ${SOURCES} ${HEADERS})

# Link the libraries to your target
target_link_libraries(${This} 
    ${WAD_READER_LIB}
    raylib
)