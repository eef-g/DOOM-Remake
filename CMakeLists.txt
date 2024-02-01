cmake_minimum_required(VERSION 3.15)

project(DOOM-Remake)

enable_testing()

set(This doom)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

enable_testing()

# Specify the paths to the libraries
set(WAD_READER_LIB "${CMAKE_SOURCE_DIR}/vendor/wad_reader/release/libwad.a")
add_library(wad_reader STATIC IMPORTED)
set_property(TARGET wad_reader PROPERTY IMPORTED_LOCATION ${WAD_READER_LIB})

# Set up the resources directory for the build
set(WAD_FILE "src/resources/wads/doom1.wad")
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/resources)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/resources/wads)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/resources/decompiled_wad_resources)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/resources/default_resources)

# Put the WAD file into the build directory
if (NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/resources/wads/doom1.wad)
    message("Copying WAD file to build directory")
    file(COPY ${WAD_FILE} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/resources/wads)
endif()

# Copy the default resources to the build directory
file(COPY ${CMAKE_SOURCE_DIR}/src/resources/default_resources/ 
     DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/resources/default_resources)

# configure_file(${WAD_FILE} ${CMAKE_CURRENT_BINARY_DIR}/resources COPYONLY)
include_directories(
    "${CMAKE_SOURCE_DIR}/src"
    "${CMAKE_SOURCE_DIR}/vendor/wad_reader/src"
    "${CMAKE_SOURCE_DIR}/build/_deps/raylib-src/src"
)


# Add the subdirectories
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


file(GLOB SOURCES 
    "src/*.cpp"
    "src/model/*.cpp"
    "src/view/*.cpp"
    "src/controller/*.cpp"
)


file (GLOB HEADERS
    "src/*.hpp"
    "src/model/*.hpp"
    "src/view/*.hpp"
    "src/controller/*.hpp"
)

set(MainFile "main.cpp")

message("${CMAKE_SOURCE_DIR}/build/_deps/raylib-src/src")



add_library(${This} STATIC ${SOURCES} ${HEADERS})
set_target_properties(doom PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib"
)

add_executable(game ${MainFile} ${SOURCES} ${HEADERS})

# Link the libraries to your target
target_link_libraries(game
    ${This}
    ${WAD_READER_LIB}
    raylib
)