cmake_minimum_required(VERSION 3.31)

project(rt-engine LANGUAGES CXX)

include(CTest)

find_package(glm REQUIRED)
find_package(glfw3 REQUIRED)
find_package(imgui REQUIRED)
find_package(Boost REQUIRED)
find_package(spdlog REQUIRED)
find_package(raylib REQUIRED)

include(FetchContent)

FetchContent_Declare(
  mono_runtime
  URL      "https://github.com/alaidine/RoarEngine/releases/download/1.0.0/mono_win64.zip"
  URL_HASH SHA256=4306fd4e4c578f93fd1caa2b2bd917765a3df3927933ae306976b865bdbc853d
)
FetchContent_MakeAvailable(mono_runtime)

set(MONO_ROOT "${mono_runtime_SOURCE_DIR}")

set(MONO_INCLUDE_DIR "${MONO_ROOT}/include/")
set(MONO_LIB_DIR     "${MONO_ROOT}/lib")
set(MONO_BIN_DIR     "${MONO_ROOT}/bin")
set(MONO_ASSEMBLIES  "${MONO_ROOT}/lib/mono/4.5")

# Put all runtime/library/archive outputs into the same directory
set(RT_ENGINE_OUT_DIR ${CMAKE_BINARY_DIR}/RTEngine)

# Single-config generators
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY     ${RT_ENGINE_OUT_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY     ${RT_ENGINE_OUT_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY     ${RT_ENGINE_OUT_DIR})
set(CMAKE_PDB_OUTPUT_DIRECTORY         ${RT_ENGINE_OUT_DIR})

# Multi-config generators (e.g., Visual Studio)
foreach(cfg IN LISTS CMAKE_CONFIGURATION_TYPES)
  string(TOUPPER "${cfg}" _cfg)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${_cfg} ${RT_ENGINE_OUT_DIR})
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${_cfg} ${RT_ENGINE_OUT_DIR})
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${_cfg} ${RT_ENGINE_OUT_DIR})
  set(CMAKE_PDB_OUTPUT_DIRECTORY_${_cfg} ${RT_ENGINE_OUT_DIR})
endforeach()

add_subdirectory(renderer)
add_subdirectory(ecs)
add_subdirectory(core)
add_subdirectory(samples)
add_subdirectory(rtmodule)

set_target_properties(samples PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}")
