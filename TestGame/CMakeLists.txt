file(GLOB_RECURSE  TEST_GAME_SOURCE_FILES "src/*.h" "src/*.cpp")
add_executable(TestGame ${TEST_GAME_SOURCE_FILES})
target_link_libraries(TestGame Engine)