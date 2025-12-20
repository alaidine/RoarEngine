cmake_minimum_required(VERSION 4.1.0)

project(rt-engine)

find_package(Vulkan REQUIRED)
find_package(glm REQUIRED)
find_package(Ktx REQUIRED)
find_package(glfw3 REQUIRED)
find_package(imgui REQUIRED)

add_subdirectory(renderer)
add_subdirectory(samples)

set_target_properties(samples PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT samples)
