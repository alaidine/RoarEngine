cmake_minimum_required(VERSION 3.24...4.1)
project(r-type)

include(FetchContent)

set(CMAKE_CXX_STANDARD 20)

# Project targets
set(CORE_LIB r-type_core)
set(CLIENT r-type_client)
set(SERVER r-type_server)

# Dependencies - use local sources if available via FETCHCONTENT_SOURCE_DIR
set(FETCHCONTENT_QUIET FALSE)

# Using URL downloads instead of Git to avoid network issues
FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/5.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
)

FetchContent_Declare(
    sol2
    URL https://github.com/ThePhD/sol2/archive/refs/tags/v3.3.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
)

FetchContent_Declare(
    box2d
    URL https://github.com/erincatto/box2d/archive/refs/tags/v3.1.1.zip
    DOWNLOAD_EXTRACT_TIMESTAMP OFF
)

# Make dependencies available
FetchContent_MakeAvailable(raylib sol2 box2d)

# Lua setup using local libraries
set(LUA_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/lua/include)
set(LUA_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/lua)

# Find lua54 library
if(WIN32)
    set(LUA_LIBRARY ${LUA_LIBRARY_DIR}/lua54.lib)
else()
    set(LUA_LIBRARY ${LUA_LIBRARY_DIR}/liblua54.a)
endif()

# Add subdirectories
add_subdirectory(core)
add_subdirectory(client)
add_subdirectory(server)
