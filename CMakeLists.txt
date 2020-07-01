cmake_minimum_required(VERSION 3.13)
project(Engine)
set(CMAKE_CXX_STANDARD 17)

find_package(Vulkan REQUIRED)

add_subdirectory(external)

file(GLOB_RECURSE  SOURCE_FILES "src/*.h" "src/*.cpp")
add_library(Engine ${SOURCE_FILES})
target_include_directories(Engine INTERFACE src)

target_link_libraries(Engine Vulkan::Vulkan glfw glm stb tinyobjloader EnTT imgui_impl tinygltf)


add_subdirectory(Editor)

add_subdirectory(TestGame)
