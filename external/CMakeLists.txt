set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(glfw)

add_subdirectory(glm)


add_library(stb INTERFACE)
target_include_directories(stb INTERFACE stb)

add_library(tinyobjloader INTERFACE)
target_include_directories(tinyobjloader INTERFACE tinyobjloader)

add_subdirectory(entt)

add_library(toml INTERFACE)
target_include_directories(toml INTERFACE tomlplusplus/include)


file(GLOB IMGUI_SOURCE_FILES "imgui/*.cpp" "imgui/*.h" "imgui/misc/*.cpp" "imgui/misc/*.h" )
add_library(imgui ${IMGUI_SOURCE_FILES})
target_include_directories(imgui INTERFACE imgui)

add_library(imgui_impl  "imgui/examples/imgui_impl_vulkan.cpp" "imgui/examples/imgui_impl_glfw.cpp ")
target_link_libraries(imgui_impl Vulkan::Vulkan glfw imgui)
target_include_directories(imgui_impl INTERFACE imgui/examples)

add_library(tinygltf INTERFACE)
target_include_directories(tinygltf INTERFACE tinygltf)

