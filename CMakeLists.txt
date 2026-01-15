cmake_minimum_required(VERSION 3.16)

project(wiff LANGUAGES CXX VERSION ${PROJECT_VERSION})

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB_RECURSE WIFF_SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

# Create library
add_library(wiff_lib ${WIFF_SOURCES})
target_include_directories(wiff_lib PUBLIC ${CMAKE_SOURCE_DIR}/src)

add_executable(wiff ${WIFF_SOURCES})

target_include_directories(wiff PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

target_compile_options(wiff PRIVATE -Wall -Wextra -Wpedantic)

install(TARGETS wiff
    RUNTIME DESTINATION /usr/bin
)

# GTesting
include(CTest)
enable_testing()

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Testing sub dir
add_subdirectory(tests)

# CPACK
set(CPACK_PACKAGE_NAME "wiff")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Chris Eberle")
set(CPACK_GENERATOR "DEB")

include(CPack)
