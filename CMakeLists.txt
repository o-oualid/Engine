cmake_minimum_required(VERSION 3.13)
project(Engine)
set(CMAKE_CXX_STANDARD 17)

find_package(Vulkan REQUIRED)

add_subdirectory(external)

file(GLOB_RECURSE  SOURCE_FILES "src/*.h" "src/*.cpp")
add_executable(Engine ${SOURCE_FILES})
target_link_libraries(Engine Vulkan::Vulkan glfw glm stb tinyobjloader)