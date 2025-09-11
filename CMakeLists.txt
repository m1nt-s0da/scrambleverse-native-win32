cmake_minimum_required(VERSION 3.15)
project(scrambleverse_win32 CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

file(GLOB_RECURSE SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_library(scrambleverse_win32 STATIC "${SRC_FILES}")

# インクルードディレクトリ
target_include_directories(scrambleverse_win32 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/scrambleverse/win32")

# Using gtest
enable_testing()
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

file(GLOB_RECURSE TEST_SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp")
add_executable(scrambleverse_win32_tests "${TEST_SRC_FILES}")
target_include_directories(scrambleverse_win32_tests PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/scrambleverse/win32")
target_link_libraries(scrambleverse_win32_tests gtest gtest_main scrambleverse_win32)
set_target_properties(scrambleverse_win32_tests PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/tests
)
add_test(NAME ScrambleverseWin32Tests COMMAND scrambleverse_win32_tests)
