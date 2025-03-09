file(GLOB_RECURSE FILES "**.c" "**.h")

add_library(core STATIC ${FILES})

target_link_libraries(core PRIVATE glfw glad stb freetype opengl32)

target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})