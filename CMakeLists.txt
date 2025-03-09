cmake_minimum_required (VERSION 3.8)

project(engine LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

include_directories(${CMAKE_SOURCE_DIR}/extern/cglm/)

add_subdirectory(core)
add_subdirectory(extern)
add_subdirectory(client)