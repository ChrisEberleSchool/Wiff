cmake_minimum_required(VERSION 3.16)

project(wiff VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Automatically find all .cpp files in src/ and subdirectories
file(GLOB_RECURSE WIFF_SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

# --- ADD THE EXECUTABLE TARGET ---
add_executable(wiff ${WIFF_SOURCES})

target_include_directories(wiff PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

# Output directly into the deb package layout
set_target_properties(wiff PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/wiff/usr/bin
)

target_compile_options(wiff PRIVATE -Wall -Wextra -Wpedantic)