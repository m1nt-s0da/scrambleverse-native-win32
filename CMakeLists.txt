cmake_minimum_required(VERSION 3.15)
project(scrambleverse_win32 CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

file(GLOB_RECURSE SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_library(scrambleverse_win32 STATIC "${SRC_FILES}")

# インクルードディレクトリ
target_include_directories(scrambleverse_win32 PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/scrambleverse/win32")
