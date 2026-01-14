cmake_minimum_required(VERSION 3.16)

project(wiff LANGUAGES CXX VERSION ${PROJECT_VERSION})

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE WIFF_SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

add_executable(wiff ${WIFF_SOURCES})

target_include_directories(wiff PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

target_compile_options(wiff PRIVATE -Wall -Wextra -Wpedantic)

install(TARGETS wiff
    RUNTIME DESTINATION /usr/bin
)

# ---- CPack ----
set(CPACK_PACKAGE_NAME "wiff")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Chris Eberle")
set(CPACK_GENERATOR "DEB")

include(CPack)
