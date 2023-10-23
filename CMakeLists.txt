cmake_minimum_required(VERSION 3.16)
project(CMakeSFMLProject LANGUAGES CXX)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "") 

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

file(GLOB Isle_SRC
    "src/*.cpp"
    "src/*.hpp"
)

add_executable(TheIsle ${Isle_SRC})
target_link_libraries(TheIsle PRIVATE sfml-graphics)
target_compile_features(TheIsle PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET TheIsle 
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:TheIsle>
        VERBATIM)
endif()

install(TARGETS TheIsle)
