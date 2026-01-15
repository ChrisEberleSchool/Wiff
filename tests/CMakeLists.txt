file(GLOB_RECURSE WIFF_TEST_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_executable(wiff_tests ${WIFF_TEST_SOURCES})

target_link_libraries(wiff_tests
    PRIVATE gtest_main
)

target_include_directories(wiff_tests PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

add_test(NAME wiff_tests COMMAND wiff_tests)
