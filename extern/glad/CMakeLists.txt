file(GLOB_RECURSE SOURCES "src/**.c" "src/**.h")
file(GLOB_RECURSE INCLUDES "include/**.h")

add_library(glad STATIC ${SOURCES})

target_include_directories(glad PUBLIC include)