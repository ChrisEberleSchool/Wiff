cmake_minimum_required(VERSION 3.16)

project(wiff LANGUAGES CXX VERSION ${PROJECT_VERSION})

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Sources
file(GLOB_RECURSE WIFF_SOURCES
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

# Library (compile sources ONCE)
add_library(wiff_lib ${WIFF_SOURCES})

target_include_directories(wiff_lib
    PUBLIC
        ${CMAKE_SOURCE_DIR}/src
)

target_compile_options(wiff_lib
    PRIVATE
        -Wall -Wextra -Wpedantic
)

# Executable (NO sources here)
add_executable(wiff src/main.cpp) # <-- ensure main.cpp exists

target_link_libraries(wiff
    PRIVATE
        wiff_lib
)

install(TARGETS wiff
    RUNTIME DESTINATION /usr/bin
)

# =========================
# Testing
# =========================
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

add_subdirectory(tests)

# =========================
# CPack
# =========================
set(CPACK_PACKAGE_NAME "wiff")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Chris Eberle")
set(CPACK_GENERATOR "DEB")

include(CPack)
