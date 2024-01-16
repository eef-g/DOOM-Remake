cmake_minimum_required(VERSION 3.15)
set(This DOOM_Testing)

file(GLOB SOURCES
    "*.cpp"
)
message("Now in ${This}")

add_executable(${This} ${SOURCES})
target_link_libraries(${This} PUBLIC
    gtest_main
    doom
    raylib
    wad_reader
)

add_test(
    NAME ${This}
    COMMAND ${This}
)