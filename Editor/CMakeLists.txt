
file(GLOB_RECURSE  EDITOR_SOURCE_FILES "src/*.h" "src/*.cpp")
add_executable(Editor ${EDITOR_SOURCE_FILES})
target_link_libraries(Editor Engine)