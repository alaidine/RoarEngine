add_executable(RoarEditor
    Editor.cpp)

target_include_directories(RoarEditor PRIVATE ${NFD_INCLUDE})
target_include_directories(RoarEditor PRIVATE ${MONO_INCLUDE_DIR})
target_include_directories(RoarEditor PRIVATE ${CMAKE_SOURCE_DIR}/renderer)
target_include_directories(RoarEditor PRIVATE ${CMAKE_SOURCE_DIR}/ecs)
target_include_directories(RoarEditor PRIVATE ${CMAKE_SOURCE_DIR}/core)
target_link_libraries(RoarEditor PRIVATE core renderer nfd raylib glm::glm imgui::imgui spdlog::spdlog)

set_target_properties(RoarEditor PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:RoarEditor>")
