add_library(core
    framework.h
    Scripting.cpp
    Scripting.h
    Event.h
    Entrypoints.h
    Inputevents.h
    Window.cpp
    Window.h
    Windowevents.h
    Application.cpp
    Application.h
    Layer.cpp
    Layer.h
    RTEConfig.h)

add_executable(CoreTests
    CoreTests.cpp
)

add_executable(RTEngine
    RTEngine.cpp
    RTEngine.h)

target_include_directories(core PRIVATE ${MONO_INCLUDE_DIR})
target_include_directories(core PRIVATE ${CMAKE_SOURCE_DIR}/renderer)
target_include_directories(core PRIVATE ${CMAKE_SOURCE_DIR}/ecs)
target_link_libraries(core PRIVATE ecs raylib boost::boost glm::glm imgui::imgui spdlog::spdlog)
target_link_libraries(core PRIVATE "${MONO_LIB_DIR}/mono-2.0-sgen.lib")

target_compile_definitions(core PRIVATE 
    MONO_LIB_PATH="${MONO_ASSEMBLIES}"
)

target_include_directories(RTEngine PRIVATE ${CMAKE_SOURCE_DIR}/renderer)
target_include_directories(RTEngine PRIVATE ${CMAKE_SOURCE_DIR}/ecs)
target_link_libraries(RTEngine PRIVATE core raylib boost::boost glm::glm imgui::imgui)

if (MSVC)
    target_link_options(RTEngine PRIVATE /FORCE:MULTIPLE)
endif()

set_target_properties(RTEngine PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/RTEngine")

if(WIN32)
    add_custom_command(TARGET RTEngine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${MONO_BIN_DIR}/mono-2.0-sgen.dll"
        $<TARGET_FILE_DIR:RTEngine>
        COMMENT "Copying Mono Runtime DLLs..."
    )
endif()

target_include_directories(CoreTests PRIVATE ${CMAKE_SOURCE_DIR}/ecs)
target_link_libraries(CoreTests PRIVATE core raylib boost::boost glm::glm imgui::imgui)

add_test(NAME TestCore
    COMMAND ${CMAKE_BINARY_DIR}/core/CoreTests)

