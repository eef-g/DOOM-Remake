cmake_minimum_required(VERSION 3.15)

project(DOOM-Remake)

enable_testing()

set(This doom)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

add_subdirectory(vendor/googletest)
add_subdirectory(test)

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
set(WAD_FILE "doom1.wad")
configure_file(${WAD_FILE} ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

file(GLOB SOURCES 
    "src/*.cpp"
)

file (GLOB HEADERS
    "src/*.hpp"
)

set(MainFile "main.cpp")

message("${CMAKE_SOURCE_DIR}/build/_deps/raylib-src/src")

include_directories(
    "${CMAKE_SOURCE_DIR}/vendor/wad_reader/src"
    "${CMAKE_SOURCE_DIR}/build/_deps/raylib-src/src"
)

add_library(${This} STATIC ${SOURCES} ${HEADERS})

add_executable(game ${MainFile})

# Link the libraries to your target
target_link_libraries(game
    ${This}
    ${WAD_READER_LIB}
    raylib
)