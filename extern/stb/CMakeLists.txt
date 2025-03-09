file(GLOB_RECURSE SOURCES "**.c")
file(GLOB_RECURSE INCLUDES "**.h")

add_library(stb STATIC ${SOURCES})

target_include_directories(stb PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})