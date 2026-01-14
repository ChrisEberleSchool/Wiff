cmake_minimum_required(VERSION 3.16)

project(wiff LANGUAGES CXX)

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

target_compile_options(wiff PRIVATE -Wall -Wextra -Wpedantic)

# --- INSTALL RULES FOR PACKAGING ---
install(TARGETS wiff
    RUNTIME DESTINATION usr/bin
)

# --- USE GIT TAG FOR VERSION ---
execute_process(
    COMMAND git describe --tags --abbrev=0
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_TAG
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

string(REGEX REPLACE "^v" "" PROJECT_VERSION "${GIT_TAG}")
message(STATUS "Project version set from Git tag: ${PROJECT_VERSION}")

# --- CPACK CONFIGURATION FOR DEB ---
set(CPACK_PACKAGE_NAME "wiff")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_CONTACT "ceber042@mtroyal.ca")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Chris Eberle")
set(CPACK_GENERATOR "DEB")

# Include architecture in the filename
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-Linux-${CMAKE_SYSTEM_PROCESSOR}")

include(CPack)
