cmake_minimum_required(VERSION 3.13)
project(Engine)
set(CMAKE_CXX_STANDARD 17)

find_package(Vulkan REQUIRED)

add_subdirectory(external)

file(GLOB_RECURSE  SOURCE_FILES "src/*.h" "src/*.cpp")
add_executable(Engine ${SOURCE_FILES})
target_link_libraries(Engine Vulkan::Vulkan glfw glm stb tinyobjloader EnTT imgui_impl)

file(GLOB_RECURSE  TESTS_SOURCE_FILES "tests/main.cpp")
add_executable(Tests ${TESTS_SOURCE_FILES})
target_link_libraries(Tests EnTT)

file(GLOB_RECURSE UI_SOURCE_FILES "tests/ui.cpp")
add_executable(UI ${UI_SOURCE_FILES})
target_link_libraries(UI Vulkan::Vulkan glfw glm stb tinyobjloader EnTT imgui imgui_impl)
