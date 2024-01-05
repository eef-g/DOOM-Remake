cmake_minimum_required(VERSION 3.15)
set(This DOOM_Testing)

file(GLOB SOURCES
    "*.cpp"
)

add_executable(${This} ${SOURCES})
target_link_libraries(${This} PUBLIC
    gtest_main
    doom
)

add_test(
    NAME ${This}
    COMMAND ${This}
)