file(GLOB_RECURSE FILES "**.c" "**.h")

add_executable(client ${FILES})

set(CONTENT_DIR "${CMAKE_SOURCE_DIR}/content")

target_link_libraries(client PRIVATE core)

target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_custom_command(TARGET client POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory ${CONTENT_DIR} $<TARGET_FILE_DIR:client>/content
	COMMENT "ñopying content directory..."
)